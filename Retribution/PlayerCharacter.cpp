#include "pch.h"
#include "PlayerCharacter.h"
#include "Game/Scenes/GameScene.h"
#include "Game/Animation/Player/PlayerAnimController.h"


int PlayerCharacter::gold = 0;
int PlayerCharacter::energy = 1;
int PlayerCharacter::energyMax = 25;
int PlayerCharacter::dodgeLimit = 1;
int PlayerCharacter::maxHealthP = 250;


PlayerCharacter::PlayerCharacter(GameScene* scene_) : Character(), counterbox(std::unique_ptr<CounterBox>()), isBlocking(false),
inputDelay(0.025f), inputTime(0), walkSpeed(200), dodgeSpeed(250), vulnerableTime(0), isVulnerable(false), cross(false)
{
	scene = scene_;

	SetMaxHealth(maxHealthP);
	SetHealth(GetMaxHealth());

	hurtBox.SetFillColour(sf::Color::Red);
	hurtBox.SetSize(20, 20);

	//Set all movment varibales to false
	left, right, up, down, parry, counter, dodge = false;

	canDodge = true;
	dodgeCount = 0;

	animationController = std::make_unique<PlayerAnimController>(this);

	animationState["Idle"] = true;
	animationState["IsDodgeing"] = false;
}


PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update(const float deltaTime_)
{
	if (!animationState["IsDodgeing"]) { 
		xSpeed = 0; 

		//Reset dodge
		if (onGround) { canDodge = true; dodgeCount = 0; }
	}

	/* Dodging should call the dodge animation causing the player to move in that direction
	when the animation is playing isDodging should be true
	*/

	if (!isVulnerable) {
		if (left || right || up || down) {
			if (dodge && canDodge) {
				inputTime += deltaTime_;
				if (inputTime >= inputDelay) {
					int x = 0;
					int y = 0;

					if (right) { x = 1; }
					else if (left) { x = -1; }

					if (up) { y = -1; }
					else if (down) { y = 1; }

					Dodge(x, y);

				}
			}
			else if (parry && animationState["Idle"] || counter && animationState["Idle"]) {
				int boxType = 0;
				if (counter) { boxType = 1; }
				inputTime += deltaTime_;
				if (inputTime >= inputDelay) {
					int x = 0;
					int y = 0;
					if (right) { x = 1; }
					else if (left) { x = -1; }

					if (up) { y = -1; }
					else if (down) { y = 1; }
					Action(x, y, boxType);
				}
			}
			else
			{
				if (animationState["Idle"]) {
					if (left) { xSpeed = -walkSpeed; }
					else if (right) { xSpeed = walkSpeed; }
				}
			}
		}
	}
	else {
		vulnerableTime -= deltaTime_;
		if (vulnerableTime <= 0) {
			isVulnerable = false;
			SetCross(false);
		}
	}
	Character::Update(deltaTime_);

	if (counterbox) { 
		counterbox->Update(deltaTime_); 
		if (counterbox->GetLife() <= 0) {
			Vulnerable();
			SetBlock(false);
			ClearBox();
		}
	}
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
	energy = 1;
	return val;
}

void PlayerCharacter::TakeDamage(int val)
{
	if (cross) { SetHealth(0); return; }
	if (isBlocking) { val - 1; }
	SetHealth(GetHealth() - val);

	energy = 0;
	SetInv(true);
	invTime = 0.3f;
}

void PlayerCharacter::ClearBox()
{
	counterbox.reset();
	animationState["Idle"] = true;
}

void PlayerCharacter::SetBlock(bool blocking)
{
	isBlocking = blocking;
}

void PlayerCharacter::Vulnerable()
{
	isVulnerable = true;
	vulnerableTime = 0.5f;
}

void PlayerCharacter::SetCross(bool value)
{
	cross = value;
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

void PlayerCharacter::Dodge(int x_, int y_)
{
	dodgeCount += 1;
	if (dodgeCount == dodgeLimit) { canDodge = false; }
	animationState["IsDodgeing"] = true;

	xSpeed = x_ * dodgeSpeed;
	ySpeed = y_ * dodgeSpeed;

	inputTime = 0;
}

void PlayerCharacter::Action(int x_, int y_, int type_)
{
	animationState["Idle"] = false;
	counterbox = std::make_unique<CounterBox>(scene, x_, y_, type_);
	inputTime = 0;
}
