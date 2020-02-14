#ifndef MONSTER_H
#define MONSTER_H
#include "../../Character.h"

class GameScene;
class Projectile;

class Monster :public Character
{
public:
	Monster(GameScene* pro);
	~Monster();

	virtual void Update(const float deltaTime);

	int dir;

	std::vector<std::unique_ptr<Projectile>> proj;

	bool IsDead();

	int GetGold();


protected: 
	int goldValue;

	float maxDelay;
	float delay;

	float detectionRange;

private:


	virtual void AI(const float deltaTime) = 0;

};
#endif // !MONSTER_H

