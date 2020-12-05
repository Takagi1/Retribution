#include "QuadSpatialPartition.h"


int QuadNode::childNum = 0;

QuadNode::QuadNode(glm::vec2 position_, float size_, QuadNode* parent_) : parent(nullptr), 
objectList(std::vector<std::weak_ptr<GameObject>>()), children()
{
	objectList.reserve(10);

	quadBounds = new BoundingBox(glm::vec2(size_), position_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}

}

QuadNode::~QuadNode()
{
	OnDestroy();
}

void QuadNode::OnDestroy()
{
	delete quadBounds;
	quadBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj.reset();
		}
		objectList.clear();
	}

	parent = nullptr;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void QuadNode::Quadify(int depth_)
{
	if (depth_ > 0 && this) {
		float half = size / 2.0f;

		//Bottom Left is neutral

		//Top Left
		children[static_cast<int>(QuadChildren::QUAD_TL)] =
			new QuadNode(glm::vec2(quadBounds->pos.x,
				quadBounds->pos.y + half),
				half, this);

		//Bottom Left
		children[static_cast<int>(QuadChildren::QUAD_BL)] =
			new QuadNode(glm::vec2(quadBounds->pos.x,
				quadBounds->pos.y),
				half, this);

		//Top Right
		children[static_cast<int>(QuadChildren::QUAD_TR)] =
			new QuadNode(glm::vec2(quadBounds->pos.x + half,
				quadBounds->pos.y + half),
				half, this);

		//Bottom Right
		children[static_cast<int>(QuadChildren::QUAD_BR)] =
			new QuadNode(glm::vec2(quadBounds->pos.x + half,
				quadBounds->pos.y),
				half, this);



		childNum += 4;

		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Quadify(depth_ - 1);
		}
	}
}

QuadNode* QuadNode::GetParent()
{
	return parent;
}

QuadNode* QuadNode::GetChild(QuadChildren childPosition_)
{
	return children[static_cast<int>(childPosition_)];
}

void QuadNode::AddCollisionObject(std::weak_ptr<GameObject> obj_)
{
	objectList.push_back(obj_);
}

void QuadNode::RemoveCollisionObject(int loc_)
{
	objectList.erase(objectList.begin() + loc_);
}

int QuadNode::GetObjectCount() const
{
	return objectList.size();
}

bool QuadNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}

	return false;
}

BoundingBox* QuadNode::GetBoundingBox() const
{
	return quadBounds;
}

int QuadNode::GetChildCount() const
{
	return childNum;
}

QuadSpatialPartition::QuadSpatialPartition(float worldSize_)
{
	root = new QuadNode(glm::vec2(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Quadify(1);
	std::cout << "There are " << root->GetChildCount() << " total child nodes" << std::endl;
	objIntersectionList = std::vector<QuadNode*>();

}

QuadSpatialPartition::~QuadSpatialPartition()
{
	OnDestroy();
}

void QuadSpatialPartition::OnDestroy()
{
	if (objIntersectionList.size() > 0) {
		for (auto cell : objIntersectionList) {
			cell = nullptr;
		}
		objIntersectionList.clear();
	}
	delete root;
	root = nullptr;
}

void QuadSpatialPartition::AddObject(std::weak_ptr<GameObject> obj_)
{
	AddObjectToCell(root, obj_);
}

std::weak_ptr<GameObject> QuadSpatialPartition::GetCollision(BoundingBox box_, std::vector<std::string> tags_)
{
	objIntersectionList.clear();
	objIntersectionList.reserve(20);
	PrepareCollisionQuery(root, box_);

	for (auto cell : objIntersectionList) {
		for (size_t i = 0; i < cell->objectList.size(); i++) {
			if (box_.Intersects(&cell->objectList[i].lock()->GetBoundingBox())) {
				for (auto t : tags_) {
					if (cell->objectList[i].lock()->GetTag() == t) {
						return cell->objectList[i];
					}
				}
			}
		}
	}
	return std::weak_ptr<GameObject>();
}

std::vector<std::weak_ptr<GameObject>> QuadSpatialPartition::GetCollisionAll(BoundingBox box_, std::vector<std::string> tags_)
{
	objIntersectionList.clear();
	objIntersectionList.reserve(20);
	PrepareCollisionQuery(root, box_);

	std::vector<std::weak_ptr<GameObject>> result;
	result.reserve(5);

	for (auto cell : objIntersectionList) {
		for (size_t i = 0; i < cell->objectList.size(); i++) {
			if (box_.Intersects(&cell->objectList[i].lock()->GetBoundingBox())) {
				for (std::string t : tags_) {
					if (cell->objectList[i].lock()->GetTag() == t) {
						//result.insert(std::end(result), cell->objectList[i]);
						result.push_back(cell->objectList[i]);
					}
				}
			}
		}
	}
	return result;
}

std::weak_ptr<GameObject> QuadSpatialPartition::GetCollision(glm::vec2 point_)
{
	objIntersectionList.clear();
	objIntersectionList.reserve(20);
	PrepareCollisionQuery(root, point_);

	std::weak_ptr<GameObject> result = std::weak_ptr<GameObject>();

	for (auto cell : objIntersectionList) {
		for (auto obj : cell->objectList) {
			obj.lock()->MouseDettection();
		}
	}

	return result;
}

void QuadSpatialPartition::RemoveObject(BoundingBox box_, std::string name_)
{
	objIntersectionList.clear();
	objIntersectionList.reserve(20);
	PrepareCollisionQuery(root, box_);

	//The intent of this loop is too force a break upon finding the GameObject in each partition. 
	//when the object is found remove it add to i and then make j a massive number to force a break.
	//this should reduce the weight of this function.
	for (size_t i = 0; i < objIntersectionList.size(); i++) {
		for (size_t j = 0; j < objIntersectionList[i]->objectList.size(); j++) {
			if (objIntersectionList[i]->objectList[j].lock()->GetName() == name_) {
				objIntersectionList[i]->RemoveCollisionObject(j);
				j = 1000;
			}
		}
	}
}

//TODO: The multiple check issue is something i would like to adress
void QuadSpatialPartition::AddObjectToCell(QuadNode* cell_, std::weak_ptr<GameObject> obj_)
{
	if (cell_ != nullptr) {
		BoundingBox box = *cell_->GetBoundingBox();
		if (box.Intersects(&obj_.lock()->GetBoundingBox())) {
			if (cell_->IsLeaf()) {
				cell_->AddCollisionObject(obj_);
			}
			else {
				for (int i = 0; i < 4; i++) {
					AddObjectToCell(cell_->GetChild(static_cast<QuadChildren>(i)), obj_);
				}
			}
		}
	}
}

void QuadSpatialPartition::PrepareCollisionQuery(QuadNode* cell_, BoundingBox box_)
{
	if (cell_ != nullptr) {
		BoundingBox box = *cell_->GetBoundingBox();
		if (box_.Intersects(&box)) {
			if (cell_->IsLeaf()) {
				objIntersectionList.push_back(cell_);
			}
			else {
				for (int i = 0; i < 4; i++) {
					PrepareCollisionQuery(cell_->GetChild(static_cast<QuadChildren>(i)), box_);
				}
			}
		}
	}
}

void QuadSpatialPartition::PrepareCollisionQuery(QuadNode* cell_, glm::vec2 point_)
{
	if (cell_ != nullptr) {
		BoundingBox box = *cell_->GetBoundingBox();
		if (box.ClickIntersect(point_)) {
			if (cell_->IsLeaf()) {
				objIntersectionList.push_back(cell_);
			}
			else {
				for (int i = 0; i < 4; i++) {
					PrepareCollisionQuery(cell_->GetChild(static_cast<QuadChildren>(i)), point_);
				}
			}
		}
	}
}