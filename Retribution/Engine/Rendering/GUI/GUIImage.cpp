#include "GUIImage.h"
#include "../../Events/MouseEventListener.h"
#include "GUIObject.h"
#include "../../Core/CoreEngine.h"
#include "../OpenGL/OpenGLSpriteSurface.h"

GUIImage::GUIImage(GUIObject* parent_) : GUIComponent(), sprite(nullptr)
{
	parent = parent_;
}

GUIImage::~GUIImage()
{
	delete sprite;
	sprite = nullptr;
}

bool GUIImage::OnCreate(std::string name_, glm::vec2 offset_, glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	switch (CoreEngine::GetInstance()->GetDrawType())
	{
	case DrawType::OpenGL:
		sprite = new OpenGLSpriteSurface(false, ShaderHandler::GetInstance()->GetShader("GUIShader"), name_, tint_);
		break;
	default:
		Debug::FatalError("No Draw Type Found", "Image.cpp", __LINE__);
		break;
	}

	UpdateTransform(parent->GetPosition(), angle_, scale_);

	return true;
}

void GUIImage::Update(const float deltaTime_)
{
}

void GUIImage::Draw(Camera* camera_)
{
	if (sprite) {
		sprite->Draw(camera_, transform);
	}
}
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
	return false;
}

void GUIImage::UpdateTransform(glm::vec2 position_, float angle_, glm::vec2 scale_)
{
	glm::mat4 transform_ = glm::mat4(1.0f);

	glm::vec2 trueScale = scale_ * sprite->GetScale();

	transform_ = glm::translate(transform_, glm::vec3(parent->GetPosition(), 0));

	transform_ = glm::translate(transform_, glm::vec3(0.5f * trueScale.x, 0.5f * trueScale.y, 0.0f)); // move origin of rotation to center of quad
	transform_ = glm::rotate(transform_, glm::radians(angle_), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	transform_ = glm::translate(transform_, glm::vec3(-0.5f * trueScale.x, -0.5f * trueScale.y, 0.0f)); // move origin back

	transform_ = glm::scale(transform_, glm::vec3(trueScale, 0));

	transform = transform_;
}
