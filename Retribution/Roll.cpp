#include "pch.h"
#include "Roll.h"
#include "Character.h"
#include "PlayerCharacter.h"


Roll::Roll() : Animation()
{
	maxTime = 2;
}


Roll::~Roll()
{

}

void Roll::Update(const float deltaTime_, Character * character_)
{
	
	
	//Start animation
	if (totalTime == 0) {
		character_->animationState["Idle"] = false;
	}

	totalTime += deltaTime_;
	if (totalTime >= 1) {
			character_->body.setFillColor(sf::Color::Yellow);
	}
	else { character_->body.setFillColor(sf::Color::Green); }

	//End animation
	if (totalTime >= maxTime) {
		character_->animationState["Idle"] = true;
	}
}
