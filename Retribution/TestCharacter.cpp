#include "pch.h"
#include "TestCharacter.h"


TestCharacter::TestCharacter() : xDir(0), idle(false), xSpeed(200), ySpeed(50), onGround(false)
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));
}


TestCharacter::~TestCharacter()
{

}

void TestCharacter::Update(const float deltaTime)
{
	int stop = 1;
	
	//gravity
	if (ySpeed < 80) { ySpeed += 3; }

	//Dont go through floor
	if (onGround && ySpeed >= 0) { stop = 0; }

	body.move(deltaTime * xSpeed * xDir, deltaTime * ySpeed * stop);
}

void TestCharacter::Jump()
{
	ySpeed = -200;
}
