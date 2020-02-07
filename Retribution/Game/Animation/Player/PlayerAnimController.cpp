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
	if (currentAnimation) {
		if (currentAnimation == animationList["Idle"]) {
			if (character->animationState["IsDodgeing"]) {
				character->animationState["Idle"] = false;
				Play("Roll");
			}
			else if (currentAnimation->totalTime >= currentAnimation->maxTime) {
				currentAnimation->RestartAnimation();
			}
		}
		else if (currentAnimation == animationList["Roll"]) {
			if (currentAnimation->totalTime >= currentAnimation->maxTime) {
				character->animationState["Idle"] = true;
				character->animationState["IsDodgeing"] = false;
				Play("Idle");
			}
		}
		currentAnimation->Update(deltaTime, character);
	}
}
