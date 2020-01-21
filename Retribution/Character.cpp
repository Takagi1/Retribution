#include "pch.h"
#include "Character.h"


Character::Character() : xDir(0), xSpeed(200), ySpeed(50), onGround(false), jump(false)
{
}


Character::~Character()
{
}

void Character::Update(const float deltaTime)
{
	int stop = 1;

	if (jump && onGround) { ySpeed = -200; }
	jump = false;

	//gravity
	if (ySpeed < 100) { ySpeed += 4; }

	//Dont go through floor
	if (onGround && ySpeed >= 0) { stop = 0; }

	body.move(deltaTime * xSpeed * xDir, deltaTime * ySpeed * stop);
}

void Character::Jump()
{
	jump = true;
}
