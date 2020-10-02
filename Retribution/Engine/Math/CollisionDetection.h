#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"

/*Function of this class is to detect all types of collisions*/


struct BoundingBox;

class CollisionDetection
{
public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator =(const CollisionDetection&) = delete;
	CollisionDetection& operator =(CollisionDetection&&) = delete;

	CollisionDetection() = delete;

	//TODO: use this for one of the graph things
	static bool AABB(const glm::vec3 pos1, const glm::vec3 size1, const glm::vec3 pos2, const glm::vec3 size2);

	~CollisionDetection();
};
#endif //! COLLISIONDETECTION_H


