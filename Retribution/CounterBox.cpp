#include "pch.h"
#include "CounterBox.h"
#include "Game/Scenes/GameScene.h"
#include "PlayerCharacter.h"
#include "Projectile.h"


CounterBox::CounterBox(GameScene* scene_, float x_ , float y_, int type_) : life(1), delay(0.5f), hangTime(false), type(type_)
{
	scene = scene_;

	body = new sf::RectangleShape(sf::Vector2f(20, 20));
	
	body->setPosition(scene->player->body.getPosition() + sf::Vector2f(scene->player->body.getSize().x * x_, scene->player->body.getSize().y * y_));
	body->setFillColor(sf::Color::Black);

}



CounterBox::~CounterBox()
{
	//Why does this break?
	//if (body != nullptr) { delete body; body = nullptr; }
}

void CounterBox::Update(const float deltaTime)
{
	if (!hangTime) {
		life -= deltaTime;
		if (life <= 0) {
			
			hangTime = true;
			if (type != 2) {
				delete body;
				body = nullptr;
			}
		}
	}
	else {
		delay -= delay;
		if (delay <= deltaTime) {
			scene->ClearBox();
		}
	}
}

void CounterBox::Trigger(std::unique_ptr<Projectile> projectile)
{
	switch (type)
	{
	//Standered Parry
	case 0:
		scene->player->AddEnergy(projectile->power);
		break;

	//Standered Counter (IE. Retribution)
	case 1:
		if (scene->player->UseEnergy() == 0) {
			projectile->caster->health -= projectile->power;
		}
		else {
			projectile->caster->health -= scene->player->UseEnergy() * projectile->power;
		}
		break;

	//Block
	case 2:
		
		//Block succseded
		if (!hangTime) {
			scene->player->AddEnergy(0.8f * projectile->power);
		}
		//Hit defended area
		else {
			//Reduce power of projectile
			if (!projectile->isBlocked) {
				projectile->power = std::floor(projectile->power / 2);
			}
		}

		break;

	//AOE Counter (IE. Wrath)
	case 3:
		break;

	//Cross Counter (IE. Judgement)
	case 4:
		break;

	default:
		Debug::Error("Counterbox type invalid", "CounterBox.cpp", __LINE__);
		break;
	}
	
	
}

const int CounterBox::GetType()
{
	return type;
}
