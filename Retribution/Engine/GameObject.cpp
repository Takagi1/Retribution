#include "../pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	hurtBox.SetObject(this);
}


GameObject::~GameObject()
{
}

bool GameObject::CollisionDetection(HurtBox* b)
{
	return hurtBox.Collision(b->GetCollider());
}

bool GameObject::CollisionDetection(sf::FloatRect b)
{
	return hurtBox.Collision(b);
}
