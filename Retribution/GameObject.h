#pragma once

#include "HurtBox.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	HurtBox hurtBox;

	bool Collision(HurtBox* b);
	bool Collision(sf::FloatRect b);
	

};

