#include "CollisionHandler.h"
#include "CollisionDetection.h"
#include "../Core/CoreEngine.h"
#include <iostream>
#include "../Rendering/Types/Image.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
QuadSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler()
{
	prevCollisions.reserve(10);
}


CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler * CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnDestroy()
{
	for (auto prev : prevCollisions) {
		prev = nullptr;
	}
	prevCollisions.clear();

	delete scenePartition;
	scenePartition = nullptr;
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	scenePartition = new QuadSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(std::weak_ptr<GameObject> go_)
{
	scenePartition->AddObject(go_);
}

void CollisionHandler::RemoveObject(BoundingBox box_, std::string name_)
{
	if (scenePartition) {
		scenePartition->RemoveObject(box_, name_);
	}
}


//Issue is that mouse Ray origin is said to be in the 10ns of thousands
void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	glm::vec2 mousePos = CollisionDetection::ClickToWorldPos(mousePosition_, 
		CoreEngine::GetInstance()->GetWindowSize(),
		CoreEngine::GetInstance()->GetCamera());

	if (scenePartition) {
		scenePartition->GetCollision(mousePosition_);

		const char* in = "pos";
		int x = mousePos.x;
		int y = mousePos.y;
		
		Debug::Info(" " + std::to_string(x) + " " + std::to_string(y), " collision", __LINE__);
	}
}

std::weak_ptr<GameObject> CollisionHandler::AABB(BoundingBox box, std::vector<std::string> tags_)
{
	if (scenePartition) {
		return scenePartition->GetCollision(box, tags_); 
	}
	return std::weak_ptr<GameObject>();
}

std::vector<std::weak_ptr<GameObject>> CollisionHandler::AABBAll(BoundingBox box, std::vector<std::string> tags_)
{
	if (scenePartition) {
		return scenePartition->GetCollisionAll(box, tags_);
	}
	return std::vector<std::weak_ptr<GameObject>>();
}
