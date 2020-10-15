#pragma once

#include "../../Engine/Rendering/GameObject.h"

/*
Rules of projectiles 

1. when the owner of the projectile dies the projectile is destroyed

*/
class Projectile : public GameObject {

public:
	Projectile(glm::vec2 position_ = glm::vec2(), const float depth_ = 0.0f);
	virtual ~Projectile();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);

	virtual void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_);

	//Getter

	int GetPower() const;

	//Setter

	void SetPower(const int power_);

private:
	int power;
};