#include "pch.h"
#include "TestCharacter.h"
#include "GameScene.h"

TestCharacter::TestCharacter(GameScene* scene_) : Character(), idle(true), energy(0)
{
	scene = scene_;
	health = 5;

	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));
	
}


TestCharacter::~TestCharacter()
{

}

void TestCharacter::Update(const float deltaTime)
{
	Character::Update(deltaTime);

	if (dx != 0 || dy != 0) {
		idle = false;
		scene->counterbox = std::make_unique<CounterBox>(scene, dx, dy);
		dx = 0;
		dy = 0;
	}
	
}

void TestCharacter::Jump()
{
	Character::Jump();
}

void TestCharacter::Damage(int val)
{
	health -= val;
	energy = 0;
	isInv = true;
	invTime = 1.5f;
}


