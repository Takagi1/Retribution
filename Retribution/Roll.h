#pragma once
#include "Animation.h"

class Character;

class Roll :
	public Animation
{
public:
	Roll();
	virtual ~Roll();

	void Update(const float deltaTime_, Character* body);


};

