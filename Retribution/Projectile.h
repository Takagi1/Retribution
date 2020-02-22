#pragma once

#include "Engine/GameObject.h"

class Monster;
class Character;

class Projectile : public GameObject
{
public:
	Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* caster);
	~Projectile();

	void Update(const float deltaTime);

	float curTime;

	Monster* caster;

	void SetPower(int power_);
	int GetPower();

	bool Collision(Character* player);

private:
	float time;
	sf::Vector2f angle;
	int power;
	
};

