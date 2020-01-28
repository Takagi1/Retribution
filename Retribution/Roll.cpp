#include "pch.h"
#include "Roll.h"
#include "Character.h"
#include "PlayerCharacter.h"


Roll::Roll() : Animation()
{
	maxTime = 0.5f;
}


Roll::~Roll()
{

}

void Roll::Update(const float deltaTime_, Character * character_)
{
	totalTime += deltaTime_;
	if (totalTime <= 0.3f) {
			character_->body.setFillColor(sf::Color::Yellow);
	}
	else { character_->body.setFillColor(sf::Color::Green); }
}
