#include "pch.h"
#include "Roll.h"


Roll::Roll() : Animation()
{
	maxTime = 3;
}


Roll::~Roll()
{
}

void Roll::Update(const float deltaTime_, sf::RectangleShape * body)
{
	totalTime += deltaTime_;
	if (totalTime > 1 && totalTime < 2) {
		body->setFillColor(sf::Color::Yellow);
	}
	else { body->setFillColor(sf::Color::Green); }

	if (totalTime >= maxTime) {
		totalTime = 0;
	}
}
