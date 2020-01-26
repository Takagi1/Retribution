#include "pch.h"
#include "AnimationController.h"
#include "Character.h"


AnimationController::AnimationController() : currentAnimation(nullptr)
{
	
}


AnimationController::~AnimationController()
{

}

void AnimationController::Play(std::string name_)
{
	currentAnimation = animationList[name_];
	currentAnimation->RestartAnimation();
}
