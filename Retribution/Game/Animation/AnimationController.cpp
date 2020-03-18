#include "../../pch.h"
#include "AnimationController.h"
#include "../../Character.h"


AnimationController::AnimationController() : currentAnimation(nullptr), animationState(0), currentAnimationState(0)
{
	
}


AnimationController::~AnimationController()
{

}

void AnimationController::SwitchAnimation(int val)
{
	animationState = val;
}

int AnimationController::GetCurrentAnimationState()
{
	return currentAnimationState;
}

void AnimationController::Play(std::string name_)
{
	currentAnimation = animationList[name_];
	currentAnimation->RestartAnimation();
}
