#pragma once
#include "../AnimationController.h"

class PlayerCharacter;

//Animation Designation
/*
0 = Idle
1 = Roll
*/
class PlayerAnimController :
	public AnimationController
{
public:
	//Must put in idle animation
	PlayerAnimController(Character* character_);
	virtual ~PlayerAnimController();

	virtual void Update(const float deltaTime) override;
};

