#include "pch.h"
#include "CounterBox.h"
#include "Game/Scenes/GameScene.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "SpacialPartition.h"


CounterBox::CounterBox(GameScene* scene_, float x_ , float y_, int type_) : life(1.0f), delay(1.0f), hangTime(false), type(type_), dirx(0), diry(0)
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
}



CounterBox::~CounterBox()
{
	//Why does this break?
	if (body != nullptr) { delete body; body = nullptr; }
}

void CounterBox::Update(const float deltaTime)
{
	if(body) {
		body->setPosition(scene->player->hurtBox.GetPosition() + sf::Vector2f(scene->player->hurtBox.GetSize().x * dirx, scene->player->hurtBox.GetSize().y * diry));
		if (Collision()) { return; }
	}


	if (!hangTime) {
		life -= deltaTime;
		if (life <= 0) {
			hangTime = true;
			delete body;
			body = nullptr;
		}
	}
	else {
		delay -= deltaTime;
		if (delay <= 0) {
			scene->player->SetBlock(false);
			scene->player->ClearBox();
		}
	}
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
		scene->player->AddEnergy(0.8f * projectile->GetPower());

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

bool CounterBox::Collision()
{
	for (auto& proj : SpacialPartition::GetInstance()->GetProjectiles()) {
		if (!proj.expired()) {
			if (body->getGlobalBounds().intersects(proj.lock()->hurtBox.GetCollider())) {
				Trigger(proj.lock());
				
				//Destroy projectile
				scene->DestroyProjectiles(proj.lock());
				//monsters[j]->proj.shrink_to_fit
				scene->player->ClearBox();
				return true;
			}
		}
	}
	return false;
}

int CounterBox::GetType() const 
{
	return type;
}
