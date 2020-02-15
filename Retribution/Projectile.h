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

	sf::Vector2f angle;

	void SetPower(int power_);
	int GetPower();

	void SetBlock(bool state_);
	bool GetBlock();

private:
	int power;
	bool isBlocked;
	
};

