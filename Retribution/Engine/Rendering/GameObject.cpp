#include "GameObject.h"
#include "Types/Image.h"
#include "SceneGraph.h"
#include "../Math/Physics2D.h"

GameObject::GameObject(glm::vec2 position_, int depth_) : angle(0)
{
	position = position_;
	depth = depth_;
}

GameObject::~GameObject()
{
	if (components.size() > 0) {
		for (auto c : components) {
			delete c;
			c = nullptr;
		}
		components.clear();
	}
}

bool GameObject::OnCreate()
{
	return true;
}

void GameObject::Update(const float deltaTime_)
{
	for (auto c : components) {
		if (!c->GetDelayUpdate()) {
			c->Update(deltaTime_);
		}
		else {
			SceneGraph::GetInstance()->AddDelayedUpdate(c);
		}
	}
}

void GameObject::Draw()
{
	//for (auto c : components) {
		//c->Draw();
	//}
}

void GameObject::Translate(glm::vec2 trans)
{
	SetPosition(GetPosition() + trans);
}

void GameObject::Rotate(float angle_)
{
	SetAngle(GetAngle() + angle);
}

void GameObject::SetPosition(glm::vec2 position_)
{
	position = position_;
	if (Image* img = GetComponent<Image>()) {
		img->UpdateTransform(position, angle, scale);
		box = img->GetBoundingBox();
		img = nullptr;
	}
}

void GameObject::SetAngle(float angle_) {
	angle = angle_;
	if (Image* img = GetComponent<Image>()) {
		img->UpdateTransform(position, angle, scale);
		img = nullptr;
	}
}

void GameObject::SetScale(glm::vec2 scale_)
{
	scale = scale_;
	if (Image* img = GetComponent<Image>()) {
		img->UpdateTransform(position, angle, scale);
		box = img->GetBoundingBox();
		img = nullptr;
	}
}

void GameObject::SetName(std::string name_)
{
	name = name_;
}

void GameObject::SetDepth(int depth_)
{
	depth = depth_;
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::AddCollisionTag(std::string tag_)
{
	collisionTags.push_back(tag_);
}


glm::vec2 GameObject::GetPosition() const
{
	return glm::vec2(position.x, position.y);
}

float GameObject::GetAngle() const {
	return angle;
}
glm::vec2 GameObject::GetScale() const
{
	return scale;
}

int GameObject::GetDepth() const
{
	return depth;
}

std::string GameObject::GetTag() const
{
	return tag;
}

bool GameObject::MouseDettection()
{
	for (auto g : components) {
		if (g->FindContainingPoint()) {
			printf("hello jim");
			return true;
		}
	}
	return false;
}

void GameObject::CollisionResponse(std::weak_ptr<GameObject> obj_)
{
	if (Physics2D* phy = GetComponent<Physics2D>()) {
		if (!phy->GetStaticObj() && phy->GetRigidBody()) {
			phy->CollisionResponse(obj_, 0);
			phy = nullptr;
		}
	}
}

BoundingBox GameObject::GetBoundingBox() const
{
	return box;
}

std::string GameObject::GetName() const
{
	return name;
}

std::vector<std::string> GameObject::GetCollisionTags() const
{
	return collisionTags;
}

void GameObject::UpdateBoundingBox(BoundingBox box_)
{
	box = box_;
}

