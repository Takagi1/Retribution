#include "pch.h"
#include "CounterBox.h"
#include "Game/Scenes/GameScene.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "SpacialPartition.h"


CounterBox::CounterBox(GameScene* scene_, float x_ , float y_, int type_) : life(1.0f), type(type_), dirx(0), diry(0)
{
	scene = scene_;


	dirx = x_;
	diry = y_;
	body = new sf::RectangleShape(sf::Vector2f(20, 20));
	
	body->setPosition(scene->player->hurtBox.GetPosition() + sf::Vector2f(scene->player->hurtBox.GetSize().x * x_, scene->player->hurtBox.GetSize().y * y_));
	body->setFillColor(sf::Color::Black);
	if (type == 2) {
		scene->player->SetBlock(true);
	}
	else if (type == 3) {
		scene->player->SetCross(true);
	}
}



CounterBox::~CounterBox()
{
	//Has broken before make sure it does not again.
	if (body != nullptr) { delete body; body = nullptr; }
	scene = nullptr;
}

void CounterBox::Update(const float deltaTime)
{
	body->setPosition(scene->player->hurtBox.GetPosition() + sf::Vector2f(scene->player->hurtBox.GetSize().x * dirx, scene->player->hurtBox.GetSize().y * diry));
	if (Collision()) { return; }

	life -= deltaTime;
}

bool CounterBox::Collision()
{
	for (auto& proj : SpacialPartition::GetInstance()->GetProjectiles()) {
		if (!proj.expired()) {
			if (body->getGlobalBounds().intersects(proj.lock()->hurtBox.GetCollider())) {
				Trigger(proj.lock());

				//Destroy projectile
				scene->DestroyProjectiles(proj.lock());

				scene->player->SetBlock(false);
				scene->player->SetCross(false);
				scene->player->ClearBox();
				return true;
			}
		}
	}
	return false;
}

void CounterBox::Trigger(std::shared_ptr<Projectile> projectile)
{
	switch (type)
	{
	//Standered Parry
	case 0:
		scene->player->AddEnergy(projectile->GetPower());
		break;

	//Standered Counter (IE. Retribution)
	case 1:
		if (scene->player->GetEnergy() == 0) {
			projectile->caster->TakeDamage(projectile->GetPower());
		}
		else {
			projectile->caster->TakeDamage(scene->player->UseEnergy() * projectile->GetPower());
		}
		break;

	//Block
	case 2:
		scene->player->AddEnergy(projectile->GetPower() - 1);

		break;

	//Cross Counter (IE. Judgement)
	case 3:
		if (scene->player->GetEnergy() == 0) {
			projectile->caster->TakeDamage(projectile->GetPower() + 2);
		}
		else {
			projectile->caster->TakeDamage(scene->player->UseEnergy() * (projectile->GetPower() + 2));
		}
		break;

	default:
		Debug::Error("Counterbox type invalid", "CounterBox.cpp", __LINE__);
		break;
	}
}

int CounterBox::GetType() const 
{
	return type;
}

float CounterBox::GetLife() const
{
	return life;
}
