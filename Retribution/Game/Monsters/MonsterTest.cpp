#include "../../pch.h"
#include "MonsterTest.h"
#include "../../Projectile.h"
#include <math.h>
#include "../Scenes/GameScene.h"

MonsterTest::MonsterTest(GameScene * game_) : Monster(game_), speed(10), minDistance(3), maxDistance(15)
{
	goldValue = 5;
	SetMaxHealth(5);
	SetHealth(GetMaxHealth());

	delay = 0;
	maxDelay = 1.0f;

	detectionRange = 25.0f;
}

MonsterTest::~MonsterTest()
{
}

void MonsterTest::Update(const float deltaTime)
{
	Monster::Update(deltaTime);
}

void MonsterTest::TakeDamage(int val)
{
	SetHealth(GetHealth() - val);
}

void MonsterTest::AI(const float deltaTime)
{
	float loc = scene->player->hurtBox.GetPosition().x - hurtBox.GetPosition().x;
	Move(loc);

	delay -= deltaTime;

	if (delay <= 0 && proj.size() < proj.capacity()) {
		Shoot();
		delay = maxDelay;
	}
}


void MonsterTest::Shoot()
{
	float y = scene->player->hurtBox.GetPosition().y - hurtBox.GetPosition().y;
	float x = scene->player->hurtBox.GetPosition().x - hurtBox.GetPosition().x;
	float angle = x + y;
	angle = sqrtf(angle);

	sf::Vector2f lim = sf::Vector2f(x / angle, y / angle);

	std::shared_ptr<Projectile>temp = std::make_shared<Projectile>(hurtBox.GetPosition(), lim, this);

	proj.push_back(temp);
	scene->proj.push_back(temp);
}


//Health Error? noted from a test 
void MonsterTest::Move(float loc)
{ 
	//If to the left
	if (loc >= 0) {
		//Out of range
		if (loc >= maxDistance) { xSpeed = speed; }
		//To close
		else if (loc <= minDistance) { xSpeed = -speed; }
	}
	//If to the right
	else if (loc < 0) {
		//Out of range
		if (loc <= -maxDistance) { xSpeed = -speed; }
		//To close
		else if (loc >= -minDistance) { xSpeed = speed; }
	}
}
