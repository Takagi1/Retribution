#include "pch.h"
#include "Monster.h"
#include "GameScene.h"
#include "Projectile.h"


Monster::Monster(GameScene* pro) : dir(1), delay(0)
{
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
		proPtr->projectiles.push_back(new Projectile(body.getPosition(), dir));
		delay = 3;
	}
}

void Monster::Jump()
{
	Character::Jump();
}
