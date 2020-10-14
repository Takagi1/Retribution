#pragma once

#include "../../Engine/Rendering/GameObject.h"

/*
Rules of projectiles 

1. when the owner of the projectile dies the projectile is destroyed

*/
class Projectile : public GameObject {

public:
	Projectile(glm::vec2 position_ = glm::vec2(), const float depth_ = 0.0f) :GameObject(position_, depth_){};
	virtual ~Projectile() {};

	virtual void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) {};
};