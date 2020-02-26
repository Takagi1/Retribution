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
	bool Collision();
	void Trigger(std::shared_ptr<Projectile> projectile);

	GameScene* scene;

	sf::RectangleShape* body;

	int GetType() const;

	float GetLife() const;

private:
	const int type;

	float life;
	float dirx;
	float diry;

};

#endif // !COUNTERBOX_H

