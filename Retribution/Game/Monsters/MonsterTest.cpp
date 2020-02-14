#include "../../pch.h"
#include "MonsterTest.h"
#include "../../Projectile.h"
#include <math.h>
#include "../Scenes/GameScene.h"

MonsterTest::MonsterTest(GameScene * game_) : Monster(game_), speed(10), minDistance(3), maxDistance(15)
{
	goldValue = 5;
	health = 5;

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

void MonsterTest::AI(const float deltaTime)
{
	float loc = scene->player->body.getPosition().x - body.getPosition().x;
	Move(loc);

	delay -= deltaTime;

	if (delay <= 0) {
		Shoot();
		delay = maxDelay;
	}
}


void MonsterTest::Shoot()
{
	float y = scene->player->body.getPosition().y - body.getPosition().y;
	float x = scene->player->body.getPosition().x - body.getPosition().x;
	float angle = x + y;
	angle = sqrtf(angle);

	sf::Vector2f lim = sf::Vector2f(x / angle, y / angle);

	proj.push_back(std::make_unique<Projectile>(body.getPosition(), lim, this));
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
