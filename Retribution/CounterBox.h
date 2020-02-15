#ifndef COUNTERBOX_H
#define COUNTERBOX_H

#include "Projectile.h"

class GameScene;

class CounterBox
{
public:

	//x_ and y_ are offset
	// pos = right/down, neg = left/up
	CounterBox(GameScene* scene_, float x_, float y_, int type_);
	~CounterBox();

	void Update(const float deltaTime);

	void Trigger(std::shared_ptr<Projectile> projectile);

	bool Collision();

	bool hangTime;

	GameScene* scene;

	sf::RectangleShape* body;

	int GetType() const;

private:
	const int type;

	float life;
	float delay;
	float dirx;
	float diry;

};

#endif // !COUNTERBOX_H

