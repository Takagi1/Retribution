#include "Image.h"
#include "../../Events/MouseEventListener.h"
#include "../GameObject.h"
#include "../../Math/CollisionDetection.h"
#include "../../Core/CoreEngine.h"

Image::Image(GameObject* parent_) : Component(), sprite(nullptr), flip(false)
{
	parent = parent_;
}

Image::~Image()
{
	//SceneGraph::GetInstance()->
	delete sprite;
	sprite = nullptr;
}

bool Image::OnCreate(GLuint shaderID, std::string name_, bool useView_, glm::vec2 offset_,
	glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;
	sprite = new SpriteSurface(useView_, shaderID, name_, scale_, angle_, tint_);

	if (sprite) {
		box.dimentions = sprite->GetScale();
		box.pos = parent->GetPosition();
	}
	return true;
}

void Image::Update(const float deltaTime_)
{
}

void Image::Draw()
{
	if (sprite) {
		sprite->Draw(CoreEngine::GetInstance()->GetCamera(), parent->GetPosition() + offset);
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

glm::vec2 Image::SetScale(const glm::vec2 scale_)
{
	sprite->SetScale(scale_);
	return sprite->GetScale();
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

		if(mousePos.x >= obbPosition.x &&
			mousePos.y >= obbPosition.y &&
			mousePos.x <= obbPosition.x + sprite->GetScale().x &&
			mousePos.y <= obbPosition.y + sprite->GetScale().y) {

			return true;
		}
	}
	return false;
} 

BoundingBox Image::GetBoundingBox() const {
	return box;
}

void Image::Flip(bool invert_)
{
	sprite->Flip(invert_);
}
