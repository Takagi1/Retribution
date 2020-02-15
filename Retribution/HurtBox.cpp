#include "pch.h"
#include "HurtBox.h"
#include "GameObject.h"

HurtBox::HurtBox()
{
}


HurtBox::~HurtBox()
{
}

void HurtBox::SetObject(GameObject* obj_)
{
	obj = obj_;
}

GameObject* HurtBox::GetGameObject() const
{
	return obj;
}

void HurtBox::SetPosition(sf::Vector2f pos_)
{
	box.setPosition(pos_);
}

void HurtBox::SetPosition(float x_, float y_)
{
	box.setPosition(x_, y_);
}

sf::Vector2f HurtBox::GetPosition() const
{
	return box.getPosition();
}

void HurtBox::SetSize(sf::Vector2f size_)
{
	box.setSize(size_);
}

void HurtBox::SetSize(float x_, float y_)
{
	box.setSize(sf::Vector2f(x_, y_));
}

sf::Vector2f HurtBox::GetSize() const
{
	return box.getSize();
}

void HurtBox::SetFillColour(sf::Color colour_)
{
	box.setFillColor(colour_);
}

void HurtBox::Move(sf::Vector2f pos_)
{
	box.move(pos_);
}

void HurtBox::Move(float x_, float y_)
{
	box.move(x_, y_);
}

bool HurtBox::Collision(sf::FloatRect colid_)
{
	return box.getGlobalBounds().intersects(colid_);
}

sf::FloatRect HurtBox::GetCollider() const
{
	return box.getGlobalBounds();
}

sf::RectangleShape HurtBox::Draw() const
{
	return box;
}
