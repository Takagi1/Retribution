#include "pch.h"
#include "Projectile.h"
#include "Game/Monsters/Monster.h"
Projectile::Projectile(sf::Vector2f pos_, int dir_, Monster* monster) : power(10), isBlocked(false)
{
	box.setPosition(pos_);
	dir = dir_;
	box.setSize(sf::Vector2f(10,10));
	box.setFillColor(sf::Color::Red);

	caster = monster;
}


Projectile::~Projectile()
{
	Debug::Info("Projectile destroyed", "Projectile.cpp", __LINE__);
}

void Projectile::Update(const float deltaTime)
{
	if (caster == nullptr) { delete this; }
	box.move(20 * dir * deltaTime, 0);
}