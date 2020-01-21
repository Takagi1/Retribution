#pragma once
#include "Projectile.h"
#include "TestCharacter.h"

class GameScene;

class CounterBox
{
public:
	CounterBox(GameScene* scene_);
	~CounterBox();

	void Update(const float deltaTime);

	void Counter(int val);

	float life;
	float delay;

	bool hangTime;

	GameScene* scene;
	TestCharacter* test;

	sf::RectangleShape* body;

};

