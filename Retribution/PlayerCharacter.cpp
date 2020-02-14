#include "pch.h"
#include "PlayerCharacter.h"
#include "Game/Scenes/GameScene.h"
#include "Game/Animation/Player/PlayerAnimController.h"


int PlayerCharacter::gold = 0;
int PlayerCharacter::energy = 0;
int PlayerCharacter::energyMax = 25;


PlayerCharacter::PlayerCharacter(GameScene* scene_) : Character(), counterbox(std::unique_ptr<CounterBox>()), parry(false), canDodge(true), dodgeLimit(1),
walkSpeed(200), dodgeSpeed(250)
{
	scene = scene_;
	health = 250;

	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));

	//Set all movment varibales to false
	left, right, up, down, parry, counter = false;

	canDodge = true;
	dodgeCount = 0;

	animationController = std::make_unique<PlayerAnimController>(this);

	animationState["Idle"] = true;
	animationState["IsDodgeing"] = false;

	inputDelay = 0.05f;
	inputTime = 0;
}


PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update(const float deltaTime_)
{
	if (!animationState["IsDodgeing"]) { xSpeed = 0; }

	//Reset dodge
	if (onGround && !animationState["IsDodgeing"]) { canDodge = true; dodgeCount = 0; }

	/* Dodging should call the dodge animation causing the player to move in that direction
	when the animation is playing isDodging should be true
	*/
	if (dodge && canDodge) {
		if (left) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {
				if (left) {

					dodgeCount += 1;
					if (dodgeCount == dodgeLimit) { canDodge = false; }
					animationState["IsDodgeing"] = true;

					xSpeed = -dodgeSpeed;

					if (up) { ySpeed = -dodgeSpeed; }
					else if (down) { ySpeed = dodgeSpeed; }
					else { ySpeed = 0; }

					inputTime = 0;
				}
			}
		}
		else if (right) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {

				dodgeCount += 1;
				if (dodgeCount == dodgeLimit) { canDodge = false; }
				animationState["IsDodgeing"] = true;

				xSpeed = dodgeSpeed;

				if (up) { ySpeed = -dodgeSpeed; }
				else if (down) { ySpeed = dodgeSpeed; }
				else { ySpeed = 0; }

				inputTime = 0;
			}
		}
		else if (up) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {
				dodgeCount += 1;
				if (dodgeCount == dodgeLimit) { canDodge = false; }
				animationState["IsDodgeing"] = true;

				ySpeed = -dodgeSpeed;
				inputTime = 0;
				
			}
		}
		else if (down) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {
				dodgeCount += 1;
				if (dodgeCount == dodgeLimit) { canDodge = false; }
				animationState["IsDodgeing"] = true;

				ySpeed = dodgeSpeed;
				inputTime = 0;
				
			}
		}
	}
	else if (parry && animationState["Idle"] || counter && animationState["Idle"]) {
		int boxType = 0;
		if (counter) { boxType = 1; }
		if (left) {  
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {
				animationState["Idle"] = false;
				if (up) { counterbox = std::make_unique<CounterBox>(scene, -1, -1, boxType); }
				else if (down) { counterbox = std::make_unique<CounterBox>(scene, -1, 1, boxType); }
				else { counterbox = std::make_unique<CounterBox>(scene, -1, 0, boxType); }
				inputTime = 0;
			}
		}
		else if (right) {
			inputTime += deltaTime_;
			if(inputTime >= inputDelay){
				animationState["Idle"] = false;
				if (up) { counterbox = std::make_unique<CounterBox>(scene, 1, -1, boxType); }
				else if (down) { counterbox = std::make_unique<CounterBox>(scene, 1, 1, boxType); }
				else { counterbox = std::make_unique<CounterBox>(scene, 1, 0, boxType); }
				inputTime = 0;
			}
		}
		else if (up) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) {
				animationState["Idle"] = false;
				counterbox = std::make_unique<CounterBox>(scene, 0, -1, boxType);
				inputTime = 0;
			}
		}
		else if (down) {
			inputTime += deltaTime_;
			if (inputTime >= inputDelay) { 
				animationState["Idle"] = false;
				counterbox = std::make_unique<CounterBox>(scene, 0, 1, boxType); }
				inputTime = 0;
		}
	}
	else
	{
		if (animationState["Idle"]) {
			if (left) { xSpeed = -walkSpeed; }
			else if (right) { xSpeed = walkSpeed; }
		}
	}
	Character::Update(deltaTime_);

	if (counterbox) { counterbox->Update(deltaTime_); }
}

int PlayerCharacter::GetEnergy() const 
{
	return energy;
}

void PlayerCharacter::AddEnergy(int value)
{
	energy += value;
	if (energy > energyMax) {
		energy = energyMax;
	}
}

int PlayerCharacter::UseEnergy()
{
	int val = energy;
	energy = 0;
	return val;
}

void PlayerCharacter::Damage(int val)
{
	health -= val;
	energy = 0;
	isInv = true;
	invTime = 10.5f;
}

void PlayerCharacter::ClearBox()
{
	counterbox.reset();
	animationState["Idle"] = true;
}

void PlayerCharacter::PresLeft() { left = true; }
void PlayerCharacter::RelLeft() { left = false; }

void PlayerCharacter::PresRight() { right = true; }
void PlayerCharacter::RelRight() { right = false; }

void PlayerCharacter::PresUp() { up = true; }
void PlayerCharacter::RelUp() { up = false; }

void PlayerCharacter::PresDown() { down = true; }
void PlayerCharacter::RelDown() { down = false; }

void PlayerCharacter::PresParry() { parry = true; }
void PlayerCharacter::RelParry() { parry = false; }

void PlayerCharacter::PresCounter() { counter = true; }
void PlayerCharacter::RelCounter() { counter = false; }

void PlayerCharacter::PresDodge() { dodge = true; }
void PlayerCharacter::RelDodge() { dodge = false; }
