#pragma once

#include "../HurtBox.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	HurtBox hurtBox;

	bool CollisionDetection(HurtBox* b);
	bool CollisionDetection(sf::FloatRect b);
	

};

