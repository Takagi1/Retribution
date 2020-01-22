#include "pch.h"
#include "TestCharacter.h"
#include "GameScene.h"

TestCharacter::TestCharacter(GameScene* scene_) : Character(), idle(true), energy(0), parry(false)
{
	scene = scene_;
	health = 5;

	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));

	//Set all movment varibales to false
	left, right, up, down, parry, counter = false;
	
}


TestCharacter::~TestCharacter()
{

}

void TestCharacter::Update(const float deltaTime)
{
	
	if (parry) {
		if(left){ scene->counterbox = std::make_unique<CounterBox>(scene, -1, dy, 0); }
		
	}
	else if (counter) {

	}
	else {
		if (idle) {
			if (left) { xDir = -1; }
			else if (right) { xDir = 1; }
			else { xDir = 0; }
		}
		else { xDir = 0; }
	}

	if (dx != 0 || dy != 0) {
		idle = false;
		

		
		dx = 0;
		dy = 0;
	}
	Character::Update(deltaTime);
}

void TestCharacter::PresLeft()
{
	left = true;
}

void TestCharacter::RelLeft()
{
	left = false;
}

void TestCharacter::PresRight()
{
	right = true;
}

void TestCharacter::RelRight()
{
	right = false;
}

void TestCharacter::PresUp()
{
	up = true;
}

void TestCharacter::RelUp()
{
	up = false;
}

void TestCharacter::PresDown()
{
	down = true;
}

void TestCharacter::RelDown()
{
	down = false;
}

void TestCharacter::PresParry()
{
	parry = true;
}

void TestCharacter::RelParry()
{
	parry = false;
}

void TestCharacter::Damage(int val)
{
	health -= val;
	energy = 0;
	isInv = true;
	invTime = 1.5f;
}


