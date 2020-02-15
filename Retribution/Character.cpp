#include "pch.h"
#include "Character.h"
#include "Game/Scenes/GameScene.h"


Character::Character() : xSpeed(0), ySpeed(0), onGround(false), inv(false), invTime(0)
{
	isDead = false;
}


Character::~Character()
{

}

void Character::Update(const float deltaTime)
{
	if (health <= 0) {
		//isDead = true;
		//return;
	}

	animationController->Update(deltaTime);

	//Invinciblity frames
	if (inv) { 
		invTime -= deltaTime;
		if (invTime <= 0) {
			SetInv(false);
		}
	}

	//gravity
	if (ySpeed < scene->gravity) { ySpeed += 4; }

	//Individual checks to see if the player is moving into ground and from what direction

	//X move
	hurtBox.Move(deltaTime * xSpeed, 0);

	if (hurtBox.Collision(scene->ground[0].getGlobalBounds())) {
		hurtBox.Move(deltaTime * -xSpeed, 0);
	}

	//Y move
	hurtBox.Move(0, deltaTime * ySpeed);

	if (hurtBox.Collision(scene->ground[0].getGlobalBounds())) {
		if (ySpeed > 0) {
			onGround = true;
		}
		hurtBox.Move(0, deltaTime * -ySpeed);
	}
	else { onGround = false; }
}

int Character::GetHealth() const
{
	return health;
}

void Character::SetHealth(int val)
{
	health = val;
}

int Character::GetMaxHealth() const
{
	return maxHealth;
}

void Character::SetMaxHealth(int val)
{
	maxHealth = val;
}

void Character::SetInv(bool stat_)
{
	inv = stat_;
}

bool Character::GetInv() const
{
	return inv;
}

void Character::SetDead(bool death)
{
	isDead = death;
}

bool Character::GetDead() const
{
	return isDead;
}

/*bool Character::Collision(sf::FloatRect colid)
{
	if (isInv == true) {
		return false;
	}
	if (hurtBox.Collision(colid)) {
		return true;
	}
	return false;
}*/

