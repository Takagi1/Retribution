#pragma once

#include "../Projectile.h"

class Character;

class Arrow : public Projectile{
public:
	Arrow(Character* parent_, glm::vec2 position_ = glm::vec2(0), float depth_ = 0.0f);
	~Arrow();


	bool OnCreate(bool isFliped_) override;
	void Update(const float deltaTime_) override;
};