#include "pch.h"
#include "CounterBox.h"
#include "GameScene.h"
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

	//if (body != nullptr) { delete body; body = nullptr; }
}

void CounterBox::Update(const float deltaTime)
{
	if (!hangTime) {
		life -= deltaTime;
		if (life <= 0) {
			hangTime = true;
			delete body;
			body = nullptr;
		}
	}
	else {
		delay -= delay;
		if (delay <= deltaTime) {
			scene->ClearBox();
		}
	}
}

void CounterBox::Trigger(Projectile* projectile)
{
	if (type == 0) {
		scene->player->energy += projectile->power;
		delete projectile;
		projectile = nullptr;
		return;
	}
	if (type == 1) {
		projectile->caster->health -= 10;
		delete projectile;
		projectile = nullptr;
		return;
	}
}
