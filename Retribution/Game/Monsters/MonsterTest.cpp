#include "../../pch.h"
#include "MonsterTest.h"
#include "../../Projectile.h"
#include "../Scenes/GameScene.h"

#include <math.h>
#include <complex>

MonsterTest::MonsterTest(GameScene * game_) : Monster(game_), speed(15), minDistance(15), maxDistance(75)
{
	goldValue = 5;
	SetMaxHealth(5);
	SetHealth(GetMaxHealth());

	maxDelay = 1.0f;

	detectionRange = 250.0f;
}

MonsterTest::~MonsterTest()
{
}

void MonsterTest::Update(const float deltaTime)
{
	Monster::Update(deltaTime);
}

void MonsterTest::Behavior(const float deltaTime)
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
	std::complex<float> div = x + y;
	div = std::sqrt(std::complex<double>(div));
	float angle;
	if (div.real() > 0) { angle = div.real(); }
	else { angle = div.imag(); }

	sf::Vector2f lim = sf::Vector2f(x / angle, y / angle);

	std::shared_ptr<Projectile>temp = std::make_shared<Projectile>(hurtBox.GetPosition(), lim, this);

	proj.push_back(temp);
	scene->projectiles.push_back(temp);
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
