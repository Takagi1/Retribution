#include "GUIImage.h"
#include "../../Events/MouseEventListener.h"
#include "GUIObject.h"
GUIImage::GUIImage() : GUIComponent()
{

}

GUIImage::~GUIImage()
{
	delete sprite;
	sprite = nullptr;
}

bool GUIImage::OnCreate(std::string name_, glm::vec2 offset_, glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	sprite = new SpriteSurface(true, ShaderHandler::GetInstance()->GetShader("GUIShader"), name_, scale_, angle_, tint_);
	return false;
}

void GUIImage::Draw(Camera* camera_)
{
	if (sprite) {
	//	sprite->Draw(camera_, parent->GetPosition());
	}
}

//TODO:check on
bool GUIImage::FindContainingPoint()
{
	if (sprite)
	{

		//glm::vec2 obbPosition = parent->GetPosition();
		//glm::vec2 mousePos = MouseEventListener::GetMousePosition();
		/*
		if (mousePos.x >= obbPosition.x &&
			mousePos.y >= obbPosition.y &&
			mousePos.x <= obbPosition.x + sprite->GetWidth() &&
			mousePos.y <= obbPosition.y + sprite->GetHeight()) {

			return true;
		}
		return false;
		*/
	}
}
