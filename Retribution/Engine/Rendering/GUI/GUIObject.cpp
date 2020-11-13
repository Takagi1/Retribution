#include "GUIObject.h"
#include "GUIImage.h"

GUIObject::GUIObject(glm::vec2 position_) : angle(0)
{
	position = position_;
}

GUIObject::~GUIObject()
{
}

bool GUIObject::OnCreate(glm::vec2 position_)
{
	position = position_;

	return false;
}

void GUIObject::Update(const float deltaTime_)
{
}

void GUIObject::Draw(Camera* camera)
{
	if (GetComponent<GUIImage>()) {
		GetComponent<GUIImage>()->Draw(camera);
	}
}

glm::vec2 GUIObject::GetPosition() const
{
	return position;
}

void GUIObject::SetPosition(glm::vec2 position_)
{
	position = position_;
	if (GetComponent<GUIImage>()) {
		GetComponent<GUIImage>()->UpdateTransform(position, angle, scale);
	}
}

void GUIObject::SetScale(glm::vec2 scale_)
{
	scale = scale_;
	if (GetComponent<GUIImage>()) {
		GetComponent<GUIImage>()->UpdateTransform(position, angle, scale);
	}
}

void GUIObject::SetName(std::string name_)
{
	name = name_;
}
