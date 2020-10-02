#include "Image.h"
#include "../../Events/MouseEventListener.h"
#include "../GameObject.h"
Image::Image() : Component()
{

}

Image::~Image()
{
	delete sprite;
	sprite = nullptr;
}

bool Image::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

bool Image::OnCreate(std::string name_, glm::vec2 offset_, glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	sprite = new SpriteSurface(ShaderHandler::GetInstance()->GetShader("GUIShader"), name_, scale_, angle_, tint_);

	if (sprite) {
		box.dimentions = glm::vec2(sprite->GetWidth(), sprite->GetHeight());
		box.pos = parent->GetPosition();
	}
	return true;
}

void Image::Draw(Camera* camera_)
{
	if (sprite) {
		sprite->Draw(camera_, parent->GetPosition() + offset);
	}
}

glm::vec2 Image::GetOffset() const
{
	return offset;
}

float Image::GetAngle() const
{
	return 0.0f;
}

glm::vec2 Image::GetScale() const
{
	return glm::vec2();
}


void Image::SetOffset(const glm::vec2 offset_)
{
	offset = offset_;
}

void Image::SetAngle(const float angle_)
{
	sprite->SetAngle(angle_);
}

void Image::SetScale(const glm::vec2 scale_)
{
	sprite->SetScale(scale_);
}

bool Image::FindContainingPoint()
{
	if (sprite)
	{

		glm::vec2 obbPosition = parent->GetPosition();
		glm::vec2 mousePos = MouseEventListener::GetMousePosition();
		
		if (mousePos.x >= obbPosition.x &&
			mousePos.y >= obbPosition.y &&
			mousePos.x <= obbPosition.x + sprite->GetWidth() &&
			mousePos.y <= obbPosition.y + sprite->GetHeight()) {

			return true;
		}
		return false;
	}
}

void Image::UpdateBox(glm::vec2 pos_)
{
	box.pos = pos_;
}
