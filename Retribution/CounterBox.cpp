#include "pch.h"
#include "CounterBox.h"
#include "GameScene.h"


CounterBox::CounterBox(GameScene* scene_) : life(2), delay(1), hangTime(false)
{
	scene = scene_;
	test = scene->test;

	body = new sf::RectangleShape(sf::Vector2f(10, 10));
	body->setPosition(test->body.getPosition() + sf::Vector2f(-5, 0));
	body->setFillColor(sf::Color::Yellow);
}


CounterBox::~CounterBox()
{
}

void CounterBox::Update(const float deltaTime)
{
	if (!hangTime) {
		life -= deltaTime;
		if (life <= 0) {
			hangTime = false;
			delete body;
			body = nullptr;
		}
	}
	else {
		delay -= delay;
		if (delay <= deltaTime) {
			scene->ClearBox();
			test->idle = false;
		}
	}
}

void CounterBox::Counter(int val)
{
	test->energy += val;
}
