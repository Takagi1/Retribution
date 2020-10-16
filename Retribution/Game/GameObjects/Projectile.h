#pragma once

#include "../../Engine/Rendering/GameObject.h"

/*
Rules of projectiles 

1. when the owner of the projectile dies the projectile is destroyed

*/
class Projectile : public GameObject {

public:
	Projectile(GameObject* parent_, glm::vec2 position_ = glm::vec2(), const float depth_ = 0.0f);
	virtual ~Projectile();

	virtual bool OnCreate(bool isFliped_);
	virtual void Update(const float deltaTime_) override;

	void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) override;

	//Getter

	int GetPower() const;
	float GetSpeed() const;

	//Setter

	void SetPower(const int power_);
	void SetSpeed(const float speed_);

private:
	int power;

	bool isFliped;

	float speed;

	GameObject* parent;
};