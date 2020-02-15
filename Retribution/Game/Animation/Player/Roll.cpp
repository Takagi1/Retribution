#include "../../../pch.h"
#include "Roll.h"
#include "../../../Character.h"
#include "../../../PlayerCharacter.h"


Roll::Roll() : Animation(), iTime(0.3f)
{
	maxTime = 0.5f;
}


Roll::~Roll()
{

}

void Roll::Update(const float deltaTime_, Character * character_)
{
	if (totalTime == 0) {
		if (character_->GetInv()) {
			if (character_->invTime <= iTime - deltaTime_) {
				character_->invTime = iTime - deltaTime_;
			}
		}
		else {
			character_->SetInv(true);
			character_->invTime = iTime - deltaTime_;
		}
	}
	totalTime += deltaTime_;

	if (totalTime <= iTime) {
			character_->hurtBox.SetFillColour(sf::Color::Yellow);
	}
	else { character_->hurtBox.SetFillColour(sf::Color::Green); 
	}
}