#include "pch.h"
#include "PlayerCharacter.h"
#include "GameScene.h"
#include "Roll.h"
#include "Kick.h"

PlayerCharacter::PlayerCharacter(GameScene* scene_) : Character(), idle(true), energy(0), parry(false), canDodge(true), dodgeLimit(1)
{
	scene = scene_;
	health = 5;

	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));

	//Set all movment varibales to false
	left, right, up, down, parry, counter = false;
	dodgeCount = 0;

	isDodgeing = false;

	animationController.character = &body;

	animationController.animationList["Roll"] = new Roll();

	inputDelay = 0.25f;
	inputTime = 0;
}


PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update(const float deltaTime)
{
	xDir = 0;

	//Reset dodge
	if (onGround && !isDodgeing) { canDodge = true; dodgeCount = 0; }

	/* Dodging should call the dodge animation causing the player to move in that direction
	when the animation is playing the player should be set to 
	*/
	if (dodge) {
		if (left || right || up || down) {
			if (left) {
			}
			else if (right) {
			}

			if (up) {
			}
			else if (down) {

			}
		}
	}
	else if (parry || counter) {
		int boxType = 0;
		if (counter) { boxType = 1; }
		if (left) { 
			inputTime += deltaTime;
			if (inputTime >= inputDelay) {
				idle = false;
				if (up) { scene->counterbox = std::make_unique<CounterBox>(scene, -1, -1, boxType); }
				else if (down) { scene->counterbox = std::make_unique<CounterBox>(scene, -1, 1, boxType); }
				else { scene->counterbox = std::make_unique<CounterBox>(scene, -1, 0, boxType); }
				inputTime = 0;
			}
		}
		else if (right) {
			inputTime += deltaTime;
			if(inputTime >= inputDelay){
				idle = false;
				if (up) { scene->counterbox = std::make_unique<CounterBox>(scene, 1, -1, boxType); }
				else if (down) { scene->counterbox = std::make_unique<CounterBox>(scene, 1, 1, boxType); }
				else { scene->counterbox = std::make_unique<CounterBox>(scene, 1, 0, boxType); }
				inputTime = 0;
			}
		}
		else if (up) {
			inputTime += deltaTime;
			if (inputTime >= inputDelay) {
				idle = false; scene->counterbox = std::make_unique<CounterBox>(scene, 0, -1, boxType);
				inputTime = 0;
			}
		}
		else if (down) {
			inputTime += deltaTime;
			if (inputTime >= inputDelay) { 
				idle = false; scene->counterbox = std::make_unique<CounterBox>(scene, 0, 1, boxType); }
				inputTime = 0;
		}
	}
	else 
	{
		if (idle) {
			if (left) { xDir = -1; }
			else if (right) { xDir = 1; }
		}
		//else { xDir = 0; }
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

void PlayerCharacter::PresCounter()
{
	counter = true;
}

void PlayerCharacter::RelCounter()
{
	counter = false;
}

void PlayerCharacter::PresDodge()
{
	dodge = true;
}

void PlayerCharacter::RelDodge()
{
	dodge = false;
}

void PlayerCharacter::Damage(int val)
{
	health -= val;
	energy = 0;
	isInv = true;
	invTime = 1.5f;
}

