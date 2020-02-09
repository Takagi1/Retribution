#pragma once

#include "Monster.h"
class MonsterTest :
	public Monster
{
public:
	MonsterTest(GameScene * game_);
	virtual ~MonsterTest();

	virtual void Update(const float deltaTime);

private:

	void AI(const float deltaTime);
};

