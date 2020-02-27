#include "../../pch.h"
#include "Monster.h"
#include "../Scenes/GameScene.h"
#include "../../Projectile.h"
#include "../Animation/Monster/MonsterAnimController.h"
#include "../Animation/Monster/MonsterIdle.h"


Monster::Monster(GameScene* pro) : Character(), dir(1), delay(0)
{

	hurtBox.SetFillColour(sf::Color::Green);
	hurtBox.SetSize(sf::Vector2f(20, 20));
	scene = pro;
	animationState["Idle"] = true;
	animationController = std::make_unique<MonsterAnimController>(this);

	animationController->animationList["Idle"] = new MonsterIdle();
	animationController->currentAnimation = animationController->animationList["Idle"];

	proj.reserve(4);
}


Monster::~Monster()
{
	OnDestroy();
}

void Monster::Update(const float deltaTime)
{
	if (health <= 0) {
		SetDead(true);
		return;
	}

	Behavior(deltaTime);

	Character::Update(deltaTime);
}

void Monster::TakeDamage(int val)
{
	SetHealth(GetHealth() - val);
}

int Monster::GetHealth() const
{
	return health;
}

int Monster::GetMaxHealth() const
{
	return maxHealth;
}

void Monster::SetHealth(int val)
{
	health = val;
}

void Monster::SetMaxHealth(int val)
{
	maxHealth = val;
}

void Monster::OnDestroy()
{
	scene->player->AddGold(goldValue);
	for (auto& trace : proj) {
		if (!trace.expired()) {
			scene->DestroyProjectiles(trace);
		}
	}
	proj.clear();
}

