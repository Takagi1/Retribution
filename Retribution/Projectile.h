#pragma once
#include "Hurtbox.h"

class Monster;

class Projectile
{
public:
	Projectile(sf::Vector2f pos_, int dir_, Monster* caster);
	~Projectile();

	void Update(const float deltaTime);

	Hurtbox box;

	Monster* caster;

	int dir;
	int power;
	bool isBlocked;
	
};

