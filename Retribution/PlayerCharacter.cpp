#include "pch.h"
#include "PlayerCharacter.h"
#include "GameScene.h"

PlayerCharacter::PlayerCharacter(GameScene* scene_) : Character(), idle(true), energy(0), parry(false)
{
	scene = scene_;
	health = 5;

	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));

	//Set all movment varibales to false
	left, right, up, down, parry, counter = false;
	
}


PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update(const float deltaTime)
{
	xDir = 0;
	if (parry || counter) {
		int boxType = 0;
		if (counter) { boxType = 1; }
		if (left) { 
			idle = false;
			if (up) { scene->counterbox = std::make_unique<CounterBox>(scene, -1, -1, boxType); }
			else if (down) { scene->counterbox = std::make_unique<CounterBox>(scene, -1, 1, boxType); }
			else { scene->counterbox = std::make_unique<CounterBox>(scene, -1, 0, boxType); }
		}
		else if (right) { 
			idle = false;
			if (up) { scene->counterbox = std::make_unique<CounterBox>(scene, 1, -1, boxType); }
			else if (down) { scene->counterbox = std::make_unique<CounterBox>(scene, 1, 1, boxType); }
			else { scene->counterbox = std::make_unique<CounterBox>(scene, 1, 0, boxType); }
		}
		else if (up) { idle = false; scene->counterbox = std::make_unique<CounterBox>(scene, 0, -1, boxType); }
		else if (down) { idle = false; scene->counterbox = std::make_unique<CounterBox>(scene, 0, 1, boxType); }

	}
	else 
	{
		if (idle) {
			if (left) { xDir = -1; }
			else if (right) { xDir = 1; }
			else { xDir = 0; }
		}
		else { xDir = 0; }
	}
	Character::Update(deltaTime);
}

void PlayerCharacter::PresLeft()
{
	left = true;
}

void PlayerCharacter::RelLeft()
{
	left = false;
}

void PlayerCharacter::PresRight()
{
	right = true;
}

void PlayerCharacter::RelRight()
{
	right = false;
}

void PlayerCharacter::PresUp()
{
	up = true;
}

void PlayerCharacter::RelUp()
{
	up = false;
}

void PlayerCharacter::PresDown()
{
	down = true;
}

void PlayerCharacter::RelDown()
{
	down = false;
}

void PlayerCharacter::PresParry()
{
	parry = true;
}

void PlayerCharacter::RelParry()
{
	parry = false;
}

void PlayerCharacter::Damage(int val)
{
	health -= val;
	energy = 0;
	isInv = true;
	invTime = 1.5f;
}

