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

	virtual void TakeDamage(int val);

	int dir;

	std::vector<std::weak_ptr<Projectile>> proj;

	int GetGold() const;

protected: 
	int goldValue;

	float maxDelay;
	float delay;

	float detectionRange;

private:

	virtual void Behavior(const float deltaTime) = 0;

};
#endif // !MONSTER_H

