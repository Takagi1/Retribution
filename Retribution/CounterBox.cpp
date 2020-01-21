#include "pch.h"
#include "CounterBox.h"
#include "GameScene.h"


CounterBox::CounterBox(GameScene* scene_, float x_ , float y_) : life(1), delay(0.5f), hangTime(false)
{
	scene = scene_;
	test = scene->test;

	body = new sf::RectangleShape(sf::Vector2f(20, 20));
	
	body->setPosition(test->body.getPosition() + sf::Vector2f(test->body.getSize().x * x_, test->body.getSize().y * y_));
	body->setFillColor(sf::Color::Black);
}



CounterBox::~CounterBox()
{
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

void CounterBox::Counter(int val)
{
	test->energy += val;
}
