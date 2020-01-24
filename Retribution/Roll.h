#pragma once
#include "Animation.h"
class Roll :
	public Animation
{
public:
	Roll();
	virtual ~Roll();

	void Update(const float deltaTime_, sf::RectangleShape* body);
};

