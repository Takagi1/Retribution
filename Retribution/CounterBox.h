#pragma once
#include "Projectile.h"
#include "TestCharacter.h"

class GameScene;




class CounterBox
{
public:

	//x_ and y_ are offset
	// pos = right/down, neg = left/up
	CounterBox(GameScene* scene_, float x_, float y_);
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

