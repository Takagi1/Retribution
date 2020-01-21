#include "pch.h"
#include "Monster.h"
#include "GameScene.h"
#include "Projectile.h"


Monster::Monster(GameScene* pro) : dir(1), delay(0)
{
	health = 5;

	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(20, 20));
	proPtr = pro;
}


Monster::~Monster()
{
	delete proPtr;
	proPtr = nullptr;
}

void Monster::Update(const float deltaTime)
{
	delay -= deltaTime;
	Character::Update(deltaTime);
	if (delay <= 0) {
		proPtr->projectiles.push_back(std::make_unique<Projectile>(body.getPosition(), dir));
		delay = 1;
	}
}

void Monster::Jump()
{
	Character::Jump();
}
