#include "CollisionDetection.h"

#include "../Core/CoreEngine.h"


CollisionDetection::~CollisionDetection()
{
}

glm::vec2 CollisionDetection::ClickToWorldPos(glm::vec2 mousePos, glm::vec2 screenSize_, Camera* camera_)
{
	glm::vec4 rayStart_NDC((mousePos.x / screenSize_.x - 0.5f) * 2.0f,
		(mousePos.y / screenSize_.y - 0.5f) * 2.0f,
		-1.0f,
		1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetOrthographic() * camera_->GetView());

	glm::vec4 rayStart_World = inverse * rayStart_NDC;
	rayStart_World /= rayStart_World.w;

	return glm::vec2 (rayStart_World.x, rayStart_World.y);

	
}
