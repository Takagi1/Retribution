#include "pch.h"
#include "TestCharacter.h"


TestCharacter::TestCharacter() : idle(false), energy(0)
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(20, 20));
}


TestCharacter::~TestCharacter()
{

}

void TestCharacter::Update(const float deltaTime)
{
	Character::Update(deltaTime);
}

void TestCharacter::Jump()
{
	Character::Jump();
}


