#include "pch.h"
#include "CounterBox.h"
#include "GameScene.h"


CounterBox::CounterBox(GameScene* scene_, int x_ , int y_) : life(2), delay(1), hangTime(false)
{
	scene = scene_;
	test = scene->test;

	body = new sf::RectangleShape(sf::Vector2f(10, 10));
	body->setPosition(test->body.getPosition() + (test->body.getSize() / 4.0f) + sf::Vector2f(test->body.getSize().x * x_, test->body.getSize().y * y_));
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
