#include "QuadSpatialPartition.h"


int QuadNode::childNum = 0;

QuadNode::QuadNode(glm::vec2 position_, float size_, QuadNode* parent_) : parent(nullptr), objectList(std::vector<GameObject*>()), children()
{
	objectList.reserve(10);

	quadBounds = new BoundingBox();
	quadBounds->pos = position_;
	quadBounds->dimentions = glm::vec2(size_);

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
			obj = nullptr;
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

		//Top Left is neutral

		//Top Left
		children[static_cast<int>(QuadChildren::QUAD_TL)] =
			new QuadNode(glm::vec2(quadBounds->pos.x,
				quadBounds->pos.y),
				half, this);

		//Bottom Left
		children[static_cast<int>(QuadChildren::QUAD_BL)] =
			new QuadNode(glm::vec2(quadBounds->pos.x,
				quadBounds->pos.y - half),
				half, this);

		//Top Right
		children[static_cast<int>(QuadChildren::QUAD_TR)] =
			new QuadNode(glm::vec2(quadBounds->pos.x + half,
				quadBounds->pos.y),
				half, this);

		//Bottom Right
		children[static_cast<int>(QuadChildren::QUAD_BR)] =
			new QuadNode(glm::vec2(quadBounds->pos.x + half,
				quadBounds->pos.y - half),
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

void QuadNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
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
	root->Quadify(2);
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

void QuadSpatialPartition::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

std::vector<GameObject*> QuadSpatialPartition::GetCollision(BoundingBox box_)
{
	objIntersectionList.reserve(20);
	PrepareCollisionQuery(root, box_);

	std::vector<GameObject*> result;
	result.reserve(5);

	for (auto cell : objIntersectionList) {
		for (auto obj : cell->objectList) {
			if (box_.Intersects(&obj->GetBoundingBox())) {
				result.push_back(obj);
			}
		}
	}
	if (result.empty()) {
		result[0] = nullptr;
	}

	return result;
}

void QuadSpatialPartition::AddObjectToCell(QuadNode* cell_, GameObject* obj_)
{
	if (cell_ != nullptr) {
		BoundingBox box = *cell_->GetBoundingBox();
		if (box.Intersects(&obj_->GetBoundingBox())) {
			if (cell_->IsLeaf()) {
				cell_->AddCollisionObject(obj_);
			}
			else {
				for (int i = 0; i < 8; i++) {
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
				for (int i = 0; i < 8; i++) {
					PrepareCollisionQuery(cell_->GetChild(static_cast<QuadChildren>(i)), box_);
				}
			}
		}
	}
}