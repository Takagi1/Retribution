#include "pch.h"
#include "PlayerAnimController.h"


PlayerAnimController::PlayerAnimController()
{
	
}

PlayerAnimController::~PlayerAnimController()
{
}

void PlayerAnimController::Update(const float deltaTime)
{
	if (currentAnimation) {
		//Changes first
		if (currentAnimation->totalTime >= currentAnimation->maxTime) {
			//TODO: Catch if player performs input moment that endAnimation is called
			currentAnimation->EndAnimation(character);
			delete currentAnimation;
			currentAnimation = nullptr;
		}
	}


	//Then call update
	AnimationController::Update(deltaTime);
}
