#pragma once
#include "../Animation.h"


class PlayerIdle :
	public Animation
{
public:
	PlayerIdle();
	~PlayerIdle();

	virtual void Update(const float deltaTime_, Character* character_);

};

