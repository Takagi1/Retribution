#include "pch.h"
#include "TestCharacter.h"


TestCharacter::TestCharacter()
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(10, 10));
}


TestCharacter::~TestCharacter()
{
}

void TestCharacter::Update(const float deltaTime)
{
	body.move(deltaTime * 200 * xDir, deltaTime * 200 * yDir);
}
