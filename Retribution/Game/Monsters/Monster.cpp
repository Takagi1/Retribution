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

	proj.reserve(15);
}


Monster::~Monster()
{
	proj.clear();
}

void Monster::Update(const float deltaTime)
{
	Behavior(deltaTime);

	Character::Update(deltaTime);
}

void Monster::TakeDamage(int val)
{
	SetHealth(GetHealth() - val);
}

int Monster::GetGold() const
{
	return goldValue;
}


