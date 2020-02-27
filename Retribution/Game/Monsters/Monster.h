#ifndef MONSTER_H
#define MONSTER_H
#include "../../Character.h"

class GameScene;
class Projectile;

class Monster :public Character
{
public:
	Monster(GameScene* pro);
	virtual ~Monster();

	virtual void Update(const float deltaTime);

	virtual void TakeDamage(int val);

	int GetHealth() const;
	int GetMaxHealth() const;

	void SetHealth(int val);
	void SetMaxHealth(int val);
	
	int dir;

	std::vector<std::weak_ptr<Projectile>> proj;

	void OnDestroy();

protected: 

	int goldValue;

	float maxDelay;
	float delay;

	float detectionRange;

private:

	int health;
	int maxHealth;

	virtual void Behavior(const float deltaTime) = 0;

};
#endif // !MONSTER_H

