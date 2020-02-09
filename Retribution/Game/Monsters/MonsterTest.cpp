#include "../../pch.h"
#include "MonsterTest.h"
#include "../../Projectile.h"

MonsterTest::MonsterTest(GameScene * game_) : Monster(game_)
{

}

MonsterTest::~MonsterTest()
{
}

void MonsterTest::Update(const float deltaTime)
{
	Monster::Update(deltaTime);
}

void MonsterTest::AI(const float deltaTime)
{
	delay -= deltaTime;

	if (delay <= 0) {

		proj.push_back(std::make_unique<Projectile>(body.getPosition(), dir, this));
		delay = 1;
	}
}
