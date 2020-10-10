#include "CollisionHandler.h"
#include "CollisionDetection.h"
#include "../Core/CoreEngine.h"
#include <iostream>

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

void CollisionHandler::AddObject(GameObject * go_)
{
	scenePartition->AddObject(go_);
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

std::vector<GameObject*> CollisionHandler::AABB(BoundingBox box)
{
	if (scenePartition) {
		return scenePartition->GetCollision(box); 
	}
}
