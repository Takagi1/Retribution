#include "pch.h"
#include "Roll.h"
#include "Character.h"
#include "PlayerCharacter.h"


Roll::Roll() : Animation()
{
	maxTime = 1;
}


Roll::~Roll()
{

}

void Roll::Update(const float deltaTime_, Character * character_)
{
	totalTime += deltaTime_;
	if (totalTime <= 1) {
			character_->body.setFillColor(sf::Color::Yellow);
	}
	else { character_->body.setFillColor(sf::Color::Green); }
}
