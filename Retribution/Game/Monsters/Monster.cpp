#include "../../pch.h"
#include "Monster.h"
#include "../Scenes/GameScene.h"
#include "../../Projectile.h"
#include "../Animation/Monster/MonsterAnimController.h"
#include "../Animation/Monster/MonsterIdle.h"


Monster::Monster(GameScene* pro) : Character(), dir(1)
{

	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(20, 20));
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
	AI(deltaTime);
	Character::Update(deltaTime);
}

bool Monster::IsDead()
{
	return isDead;
}

int Monster::GetGold()
{
	return goldValue;
}


