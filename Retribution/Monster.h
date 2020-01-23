#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"

class GameScene;

class Monster :public Character
{
public:
	Monster(GameScene* pro);
	virtual ~Monster();


	virtual void Update(const float deltaTime);

	int dir;

	float delay;

	std::shared_ptr<Monster> projectCon;
};
#endif // !MONSTER_H

