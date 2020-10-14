#include "GameObject.h"
#include "Types/Image.h"
GameObject::GameObject(glm::vec2 position_, float depth_) : angle(0)
{
	position = glm::vec3(position_,depth_);
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
		c->Update(deltaTime_);
	}
}

void GameObject::Draw(Camera* camera_)
{
	for (auto c : components) {
		c->Draw(camera_);
	}
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
	position = glm::vec3(position_, position.z);
	if (GetComponent<Image>()) {
		box.pos = position_;
	}
}

void GameObject::SetAngle(float angle_) {
	angle = angle_;
	if (GetComponent<Image>()) {
		GetComponent<Image>()->SetAngle(angle);
	}
}

void GameObject::SetScale(glm::vec2 scale_)
{
	scale = scale_;
	if (GetComponent<Image>()) {
		box.dimentions = GetComponent<Image>()->SetScale(scale_);
	}
}

void GameObject::SetName(std::string name_)
{
	name = name_;
}

void GameObject::SetDepth(float depth_)
{
	position.z = depth_;
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
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

float GameObject::GetDepth() const
{
	return position.z;
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

BoundingBox GameObject::GetBoundingBox() const
{
	return box;
}

std::string GameObject::GetName() const
{
	return name;
}

void GameObject::UpdateBoundingBox(BoundingBox box_)
{
	box = box_;
}

