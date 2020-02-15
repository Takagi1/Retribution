#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	hurtBox.SetObject(this);
}


GameObject::~GameObject()
{
}

bool GameObject::Collision(HurtBox* b)
{

	return hurtBox.Collision(b->GetCollider());
}

bool GameObject::Collision(sf::FloatRect b)
{
	return hurtBox.Collision(b);
}
