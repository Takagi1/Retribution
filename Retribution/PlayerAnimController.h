#pragma once
#include "AnimationController.h"

class PlayerCharacter;

class PlayerAnimController :
	public AnimationController
{
public:
	PlayerAnimController();
	virtual ~PlayerAnimController();

	virtual void Update(const float deltaTime);
};

