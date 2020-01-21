#include "pch.h"
#include "Projectile.h"


Projectile::Projectile(sf::Vector2f pos_, int dir_) : energy(10)
{
	box.setPosition(pos_);
	dir = dir_;
	box.setSize(sf::Vector2f(10,10));
	box.setFillColor(sf::Color::Red);
}


Projectile::~Projectile()
{
}

void Projectile::Update(const float deltaTime)
{
	box.move(10 * dir * deltaTime, 0);
}
