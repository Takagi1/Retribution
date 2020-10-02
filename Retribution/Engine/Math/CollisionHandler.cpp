#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
//OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

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

	//delete scenePartition;
	//scenePartition = nullptr;
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	//scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject * go_)
{
	//scenePartition->AddObject(go_);
}

//Issue is that mouse Ray origin is said to be in the 10ns of thousands
void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{/*
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_,
		CoreEngine::GetInstance()->GetWindowSize(),
		CoreEngine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollisions) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
				c = nullptr;
			}
		}
		prevCollisions.clear();

		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
	*/
}
