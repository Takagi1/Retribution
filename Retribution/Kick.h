#pragma once
#include "Animation.h"

class Kick :
	public Animation
{
public:
	Kick();
	virtual ~Kick();

	virtual void Update(const float deltaTime_, sf::RectangleShape* body);
};

