#pragma once
#include "Hurtbox.h"

class Projectile
{
public:
	Projectile(sf::Vector2f pos_, int dir_);
	~Projectile();

	void Update(const float deltaTime);

	Hurtbox box;

	int dir;
	int power;
	
};

