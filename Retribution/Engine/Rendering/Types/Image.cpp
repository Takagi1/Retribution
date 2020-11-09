#include "Image.h"
#include "../../Events/MouseEventListener.h"
#include "../GameObject.h"
#include "../../Math/CollisionDetection.h"
#include "../../Core/CoreEngine.h"
#include "../OpenGL/OpenGLSpriteSurface.h"
#include "../../Core/CoreEngine.h"


//TODO: Can make improvement with rendering by having a update for sprite's transform.

Image::Image(GameObject* parent_) : Component(), sprite(nullptr), flip(false), type(DrawType::OpenGL), depth(0), 
transform(glm::mat4(0))
{
	parent = parent_;
}

Image::~Image()
{
	//SceneGraph::GetInstance()->
	delete sprite;
	sprite = nullptr;
}

bool Image::OnCreate(GLuint shaderID, std::string name_, bool useView_, float depth_, glm::vec2 offset_,
	glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	offset = offset_;

	depth = depth_;

	switch (CoreEngine::GetInstance()->GetDrawType())
	{
	case DrawType::OpenGL:
		sprite = new OpenGLSpriteSurface(useView_, shaderID, name_, scale_, angle_, tint_);
		break;
	default:
		Debug::FatalError("No Draw Type Found", "Image.cpp", __LINE__);
		break;
	}

	if (sprite) {
		box.dimentions = sprite->GetScale();
		box.pos = parent->GetPosition();
		SceneGraph::GetInstance()->AddImage(this, shaderID);
		return true;
	}
	return false;
}

void Image::Update(const float deltaTime_)
{
}

void Image::Draw()
{
	if (sprite) {
		sprite->Draw(CoreEngine::GetInstance()->GetCamera(), transform);
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

void Image::UpdateTransform(glm::vec2 position_, float angle_, glm::vec2 scale_)
{
	glm::mat4 transform_ = glm::mat4(1.0f);

	glm::vec2 trueScale = scale_ * sprite->GetScale();

	transform_ = glm::translate(transform_, glm::vec3(position_, depth));

	transform_ = glm::translate(transform_, glm::vec3(0.5f * trueScale.x, 0.5f * trueScale.y, 0.0f)); // move origin of rotation to center of quad
	transform_ = glm::rotate(transform_, glm::radians(angle_), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	transform_ = glm::translate(transform_, glm::vec3(-0.5f * trueScale.x, -0.5f * trueScale.y, 0.0f)); // move origin back

	transform_ = glm::scale(transform_, glm::vec3(trueScale, 0));


	box.dimentions = trueScale;
	box.pos = position_;
	transform = transform_;
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


