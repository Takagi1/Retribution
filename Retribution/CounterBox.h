#ifndef COUNTERBOX_H
#define COUNTERBOX_H

#include "Projectile.h"
#include "TestCharacter.h"

class GameScene;

class CounterBox
{
public:

	//x_ and y_ are offset
	// pos = right/down, neg = left/up
	CounterBox(GameScene* scene_, float x_, float y_, int type_);
	~CounterBox();

	void Update(const float deltaTime);

	void Trigger(int val);

	float life;
	float delay;

	bool hangTime;

	GameScene* scene;
	TestCharacter* test;

	sf::RectangleShape* body;

private:
	const int type;

};

#endif // !COUNTERBOX_H

