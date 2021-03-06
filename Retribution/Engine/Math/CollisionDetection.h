#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"

/*Function of this class is to detect collisions between different class types*/

struct BoundingBox;

class CollisionDetection{

public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator =(const CollisionDetection&) = delete;
	CollisionDetection& operator =(CollisionDetection&&) = delete;

	CollisionDetection() = delete;

	~CollisionDetection();

	static glm::vec2 ClickToWorldPos(glm::vec2 mousePos, glm::vec2 screenSize_, Camera* camera_);


};
#endif //! COLLISIONDETECTION_H


