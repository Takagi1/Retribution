#pragma once

#include "GameObject.h"

class Monster;

class Projectile : public GameObject
{
public:
	Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* caster);
	~Projectile();

	void Update(const float deltaTime);

	Monster* caster;

	void SetPower(int power_);
	int GetPower();

private:
	sf::Vector2f angle;
	int power;
	
};

