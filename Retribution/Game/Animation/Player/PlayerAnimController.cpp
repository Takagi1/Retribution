#include "../../../pch.h"
#include "PlayerAnimController.h"
#include "../../../Character.h"
#include "PlayerIdle.h"
#include "Roll.h"

PlayerAnimController::PlayerAnimController(Character* character_) : AnimationController()
{
	character = character_;
	animationList["Idle"] = new PlayerIdle();
	animationList["Roll"] = new Roll();

	currentAnimation = animationList["Idle"];
}

PlayerAnimController::~PlayerAnimController()
{

}

void PlayerAnimController::Update(const float deltaTime)
{
	//Animation paths
	switch (currentAnimationState) {

	case 0:
		//Trans to example
		if (animationState == 1) {
			currentAnimationState = 1;
			Play("Roll");
		}
		//Restart
		else if (currentAnimation->totalTime >= currentAnimation->maxTime) {
			currentAnimation->RestartAnimation();
		}

		break;
	case 1:
		if (currentAnimation->totalTime >= currentAnimation->maxTime) {
			SwitchAnimation(0);
			currentAnimationState = 0;
			Play("Idle");
		}
	default:
		break;
	}
	currentAnimation->Update(deltaTime, character);
}
