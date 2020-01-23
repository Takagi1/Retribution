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
	proj.clear();
}

void Monster::Update(const float deltaTime)
{
	if (health <= 0) {
		isDead = true;
		return;
	}
	Character::Update(deltaTime);

	delay -= deltaTime;
	
	if (delay <= 0) {
		
		proj.push_back(std::make_unique<Projectile>(body.getPosition(), dir, this));
		delay = 1;
	}
}

bool Monster::IsDead()
{
	return isDead;
}
