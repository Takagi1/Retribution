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

	virtual void TakeDamage(int val) = 0;

	int dir;

	std::vector<std::shared_ptr<Projectile>> proj;

	int GetGold() const;

	void UpdateProj(const float deltaTime);


protected: 
	int goldValue;

	float maxDelay;
	float delay;

	float detectionRange;

private:


	virtual void AI(const float deltaTime) = 0;

};
#endif // !MONSTER_H

