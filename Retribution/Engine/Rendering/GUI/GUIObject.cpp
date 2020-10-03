#include "GUIObject.h"

GUIObject::GUIObject(glm::vec2 position_) : rotation(0)
{
	position = position_;
}

GUIObject::~GUIObject()
{
}

bool GUIObject::OnCreate()
{
	return true;
}

void GUIObject::Update(const float deltaTime_)
{
}

void GUIObject::Draw(Camera* camera_)
{
	for (auto c : guiComponents) {
		c->Draw(camera_);
	}
}

void GUIObject::SetPosition(glm::vec2 position_)
{
	position = position_;
}

void GUIObject::SetRotation(float rotation_)
{
	rotation = rotation_;
}

void GUIObject::SetScale(glm::vec2 scale_)
{
	scale = scale_;
}

void GUIObject::SetTag(std::string tag_)
{
	tag = tag_;
}

glm::vec2 GUIObject::GetPosition() const
{
	return position;
}

float GUIObject::GetRotation() const
{
	return rotation;
}

glm::vec2 GUIObject::GetScale() const
{
	return scale;
}

bool GUIObject::MouseDettection()
{
	for (auto g : guiComponents) {
		if (g->FindContainingPoint()) {
			return true;
		}
	}
	return false;
}
