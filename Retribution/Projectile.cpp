#include "pch.h"
#include "Projectile.h"
#include "Game/Monsters/Monster.h"
#include "SpacialPartition.h"

Projectile::Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* monster) : power(10)
{
	hurtBox.SetPosition(pos_);
	angle = angle_;
	hurtBox.SetSize(10,10);
	hurtBox.SetFillColour(sf::Color::Red);

	caster = monster;

	time = 3;
	curTime = time;
}


Projectile::~Projectile()
{
	Debug::Info("Projectile destroyed", "Projectile.cpp", __LINE__);
}

void Projectile::Update(const float deltaTime)
{
	curTime -= deltaTime;
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

bool Projectile::Collision(Character* player)
{
	if (curTime <= 0) {
		return true;
	}

	if (!player->GetInv()) {
		if (CollisionDetection(player->hurtBox.GetCollider())) {
			player->TakeDamage(GetPower());
			return true;
		}
	}
	for (auto& gro : SpacialPartition::GetInstance()->GetGround()) {
		if (CollisionDetection(gro)) {
			return true;
		}
	}

	return false;
}

