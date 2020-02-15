#include "../../pch.h"
#include "Monster.h"
#include "../Scenes/GameScene.h"
#include "../../Projectile.h"
#include "../Animation/Monster/MonsterAnimController.h"
#include "../Animation/Monster/MonsterIdle.h"


Monster::Monster(GameScene* pro) : Character(), dir(1)
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
	if (proj.size() > 0) { UpdateProj(deltaTime); }

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

void Monster::UpdateProj(const float deltaTime)
{
	for (int i = 0; i < proj.size();) {
		proj[i]->Update(deltaTime);

		if (proj[i]->Collision(&scene->player->hurtBox)) {
			scene->player->Damage(proj[i]->GetPower());
			proj.erase(proj.begin() + i);
			continue;
		}

		bool kick = false;
		for (auto& gro : scene->ground) {
			if (proj[i]->Collision(gro.getGlobalBounds())) {
				proj.erase(proj.begin() + i);
				kick = true;
				break;
			}
		}

		if (!kick) { i++; }
	}
}


