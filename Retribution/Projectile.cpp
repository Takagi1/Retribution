#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos_, int dir_) : power(10)
{
	box.setPosition(pos_);
	dir = dir_;
	box.setSize(sf::Vector2f(10,10));
	box.setFillColor(sf::Color::Red);
}


Projectile::~Projectile()
{
	Debug::Info("Projectile destroyed", "Projectile.cpp", __LINE__);
}

void Projectile::Update(const float deltaTime)
{
	box.move(20 * dir * deltaTime, 0);
}
