#include "pch.h"
#include "Character.h"


Character::Character() : xDir(0), xSpeed(200), ySpeed(50), onGround(false), jump(false), isInv(false), invTime(0)
{
}


Character::~Character()
{
	delete scene;
	scene = nullptr;
}

void Character::Update(const float deltaTime)
{
	if (health <= 0) {
		//TODO: Cause character to die
		//return;
	}

	//Invinciblity frames
	if (isInv) { 
		if (invTime -= deltaTime <= 0) {
			isInv = false;
		}
	}

	int stop = 1;

	if (jump && onGround) { ySpeed = -200; }
	jump = false;

	//gravity
	if (ySpeed < 100) { ySpeed += 4; }

	//Dont go through floor
	if (onGround && ySpeed >= 0) { stop = 0; }


	body.move(deltaTime * xSpeed * xDir, deltaTime * ySpeed * stop);
	
}

bool Character::Collision(sf::FloatRect colid)
{
	if (colid.intersects(body.getGlobalBounds()) && isInv == false) {
		return true;
	}
	return false;
}

