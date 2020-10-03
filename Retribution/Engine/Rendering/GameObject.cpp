#include "GameObject.h"
#include "Types/Image.h"
GameObject::GameObject(glm::vec2 position_, float depth_) : angle(0)
{
	position = glm::vec3(position_,depth_);
}

GameObject::~GameObject()
{
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

void GameObject::SetPosition(glm::vec2 position_)
{
	position = glm::vec3(position_, position.z);
	if (GetComponent<Image>()) {
		GetComponent<Image>()->UpdateBox(position_);
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
		GetComponent<Image>()->SetScale(scale_);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetDepth(float depth_)
{
	position.z = depth_;
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

bool GameObject::MouseDettection()
{
	for (auto g : components) {
		if (g->FindContainingPoint()) {
			return true;
		}
	}
	return false;
}
