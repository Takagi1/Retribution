#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../Rendering/GameObject.h"
#include "../Core/QuadSpatialPartition.h"

class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator =(const CollisionHandler&) = delete;
	CollisionHandler& operator =(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();
	void OnDestroy();
	void OnCreate(float worldSize_);
	void AddObject(std::weak_ptr<GameObject> go_);
	void RemoveObject(BoundingBox box_, std::string name_);

	void MouseUpdate(glm::vec2 mousePosition_, int buttonType_);


	std::weak_ptr<GameObject> AABB(BoundingBox box, std::vector<std::string> tag_);
	std::vector<std::weak_ptr<GameObject>> AABBAll(BoundingBox box, std::vector<std::string> tag_);

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	
	static std::vector<GameObject*> prevCollisions;

	//static std::vector

	static QuadSpatialPartition* scenePartition;

};
#endif // !COLLISIONHANDLER_H
