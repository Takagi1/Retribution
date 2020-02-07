#include "pch.h"
#include "Character.h"
#include "Game/Scenes/GameScene.h"


Character::Character() : xSpeed(0), ySpeed(0), onGround(false), isInv(false), invTime(0)
{
	isDead = false;
}


Character::~Character()
{

}

void Character::Update(const float deltaTime)
{
	animationController->Update(deltaTime);

	//Invinciblity frames
	if (isInv) { 
		invTime -= deltaTime;
		if (invTime <= 0) {
			isInv = false;
		}
	}

	//gravity
	if (ySpeed < scene->gravity) { ySpeed += 4; }

	//Individual checks to see if the player is moving into ground and from what direction
	//TODO: Improve the method of pushing the player out of the ground as this could cause some problems and is seems messy

	//X move
	body.move(deltaTime * xSpeed, 0);

	if (body.getGlobalBounds().intersects(scene->ground.getGlobalBounds())) {
		body.move(deltaTime * -xSpeed, 0);
	}

	//Y move
	body.move(0, deltaTime * ySpeed);

	if (body.getGlobalBounds().intersects(scene->ground.getGlobalBounds())) {
		if (ySpeed > 0) {
			onGround = true;
		}
		body.move(0, deltaTime * -ySpeed);
	}
	else { onGround = false; }
}

bool Character::Collision(sf::FloatRect colid)
{
	if (isInv == true) {
		return false;
	}
	if (colid.intersects(body.getGlobalBounds())) {
		return true;
	}
	return false;
}

