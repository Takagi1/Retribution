#pragma once

#include "../Character.h"

class Monster : public Character {
public:
	Monster(glm::vec2 position_, float depth_);
	~Monster();
};
