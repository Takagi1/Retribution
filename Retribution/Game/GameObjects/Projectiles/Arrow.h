#pragma once

#include "../Projectile.h"

class Arrow : public Projectile{
public:
	Arrow(GameObject* parent_, glm::vec2 position_ = glm::vec2(0), float depth_ = 0.0f);
	~Arrow();


	bool OnCreate(bool isFliped_) override;
	void Update(const float deltaTime_) override;
};