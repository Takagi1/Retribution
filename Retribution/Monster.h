#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"

class GameScene;
class Projectile;

class Monster :public Character
{
public:
	Monster(GameScene* pro);
	~Monster();

	virtual void Update(const float deltaTime);

	int dir;

	float delay;

	std::vector<std::unique_ptr<Projectile>> proj;

	bool IsDead();

	

};
#endif // !MONSTER_H

