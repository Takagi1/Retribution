#pragma once

#include "../Projectile.h"

class Arrow : public Projectile{
public:
	Arrow(glm::vec2 position_ = glm::vec2(0), float depth_ = 0.0f);
	~Arrow();

	void Update(const float deltaTime_) override;
};