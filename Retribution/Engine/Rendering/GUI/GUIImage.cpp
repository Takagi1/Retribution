#include "GUI_Image.h"
#include "../../../Events/MouseEventListener.h"
#include "GUI_Object.h"
GUI_Image::GUI_Image() : GUI_Component()
{

}

GUI_Image::~GUI_Image()
{
	delete sprite;
	sprite = nullptr;
}

bool GUI_Image::OnCreate(std::string name_, glm::vec2 offset_, glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	sprite = new SpriteSurface(ShaderHandler::GetInstance()->GetShader("GUIShader"), name_, scale_, angle_, tint_);
	return false;
}

void GUI_Image::Draw(Camera* camera_)
{
	if (sprite) {
		sprite->Draw(camera_, parent->GetPosition());
	}
}

//TODO:check on
bool GUI_Image::FindContainingPoint()
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
