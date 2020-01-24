#include "pch.h"
#include "AnimationController.h"


AnimationController::AnimationController() : currentAnimation(nullptr)
{

}


AnimationController::~AnimationController()
{

}

void AnimationController::Update(const float deltaTime_)
{
	if (currentAnimation != nullptr) {
		currentAnimation->Update(deltaTime_, character);
	}
}

void AnimationController::Play(std::string name_)
{
	currentAnimation = animationList[name_];
}
