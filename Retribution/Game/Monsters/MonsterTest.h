#pragma once

#include "Monster.h"

class MonsterTest :
	public Monster
{
public:
	MonsterTest(GameScene * game_);
	virtual ~MonsterTest();

	virtual void Update(const float deltaTime);

	virtual void TakeDamage(int val);

private:

	float speed;

	float minDistance;

	float maxDistance;

	virtual void AI(const float deltaTime);

	void Shoot();

	void Move(float loc);
};

