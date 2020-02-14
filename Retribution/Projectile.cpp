#include "pch.h"
#include "Projectile.h"
#include "Game/Monsters/Monster.h"
Projectile::Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* monster) : power(10), isBlocked(false)
{
	box.setPosition(pos_);
	angle = angle_;
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
	if (caster == nullptr) { 
		delete this; 
		return;
	}

	box.move(10 * angle.x * deltaTime, 10 * angle.y * deltaTime);

}
bool Projectile::Collision(sf::FloatRect ground_)
{
	return false;
}

