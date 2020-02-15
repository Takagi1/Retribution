#include "pch.h"
#include "Projectile.h"
#include "Game/Monsters/Monster.h"
Projectile::Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* monster) : power(10)
{
	hurtBox.SetPosition(pos_);
	angle = angle_;
	hurtBox.SetSize(10,10);
	hurtBox.SetFillColour(sf::Color::Red);

	caster = monster;
}


Projectile::~Projectile()
{
	Debug::Info("Projectile destroyed", "Projectile.cpp", __LINE__);
	delete caster;
	caster = nullptr;
}

void Projectile::Update(const float deltaTime)
{
	hurtBox.Move(10 * angle.x * deltaTime, 10 * angle.y * deltaTime);
}

void Projectile::SetPower(int power_)
{
	power = power_;
}

int Projectile::GetPower()
{
	return power;
}

