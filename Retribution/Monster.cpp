#include "pch.h"
#include "Monster.h"
#include "GameScene.h"
#include "Projectile.h"


Monster::Monster(GameScene* pro) : Character(), dir(1), delay(0)
{
	health = 5;

	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(20, 20));
	scene = pro;
}


Monster::~Monster()
{

}

void Monster::Update(const float deltaTime)
{
	delay -= deltaTime;
	Character::Update(deltaTime);
	if (delay <= 0) {
		scene->projectiles.push_front(std::make_unique<Projectile>(body.getPosition(), dir, this));
		delay = 1;
	}
}
