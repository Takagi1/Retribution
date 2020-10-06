#include "Image.h"
#include "../../Events/MouseEventListener.h"
#include "../GameObject.h"
#include "../../Math/CollisionDetection.h"
#include "../../Core/CoreEngine.h"
Image::Image(GameObject* parent_) : Component(), sprite(nullptr)
{
	parent = parent_;
}

Image::~Image()
{
	delete sprite;
	sprite = nullptr;
}

glm::vec2 Image::OnCreate(GLuint shaderID, std::string name_, bool useView_, glm::vec2 offset_,
	glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	sprite = new SpriteSurface(useView_, shaderID, name_, scale_, angle_, tint_);

	if (sprite) {
		box.dimentions = glm::vec2(sprite->GetWidth(), sprite->GetHeight());
		box.pos = parent->GetPosition();
	}
	return box.dimentions;
}

void Image::Update(const float deltaTime_)
{
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

//I think the way find is done here is horse shit and i want to fix it

bool Image::FindContainingPoint()
{
	if (sprite)
	{
		glm::vec2 obbPosition = parent->GetPosition();
		glm::vec2 mousePos = MouseEventListener::GetMousePosition();
		
		mousePos = CollisionDetection::ClickToWorldPos(mousePos, 
			CoreEngine::GetInstance()->GetWindowSize(),
			CoreEngine::GetInstance()->GetCamera());

		//TODO: why is this the way it is? it seems like the image is not being displayed in the same 
		//Place as the object nor is it displaying from the top left? could it be that it is displaying
		//from the center of the object? if so then I will have to adjust that to get accurate display.
		if (mousePos.x <= obbPosition.x &&
			mousePos.y <= obbPosition.y &&
			mousePos.x >= obbPosition.x - sprite->GetWidth() /1200 && 
			mousePos.y >= obbPosition.y - sprite->GetHeight() / 1200) {

			return true;
		}
	}
	return false;
}
