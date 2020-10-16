#include "Projectile.h"

Projectile::Projectile(glm::vec2 position_, const float depth_) :GameObject(position_, depth_), 
power(0), isRight_(false)
{
}

Projectile::~Projectile()
{
}

bool Projectile::OnCreate()
{
	return false;
}

void Projectile::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}

void Projectile::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
}

int Projectile::GetPower() const
{
	return power;
}

void Projectile::SetPower(const int power_)
{
	power = power_;
}
