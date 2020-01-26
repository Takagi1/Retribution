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
	
	//Start animation
	if (totalTime == 0) {
		character_->animationState["Idle"] = false;
		character_->animationState["IsDodgeing"] = true;
	}

	totalTime += deltaTime_;
	if (totalTime <= 1) {
			character_->body.setFillColor(sf::Color::Yellow);
	}
	else { character_->body.setFillColor(sf::Color::Green); }


}

void Roll::EndAnimation(Character* character_)
{
	//End animation
	if (totalTime >= maxTime) {
		character_->animationState["Idle"] = true;
		character_->animationState["IsDodgeing"] = false;
	}
}
