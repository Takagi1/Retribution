#pragma once
#include "Projectile.h"
#include "TestCharacter.h"

class GameScene;




class CounterBox
{
public:

	//Dir is is offset
	// pos = right/down, neg = left/up
	CounterBox(GameScene* scene_, int x_, int y_);
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

