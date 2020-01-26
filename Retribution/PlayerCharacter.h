#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
class GameScene;

class PlayerCharacter : public Character
{

public:
	PlayerCharacter(GameScene* scene);
	virtual ~PlayerCharacter();

	static int gold;

	void Update(const float deltaTime);

	int GetEnergy();
	void AddEnergy(int value);

//Input Handeling
	void PresLeft();
	void RelLeft();

	void PresRight();
	void RelRight();

	void PresUp();
	void RelUp();

	void PresDown();
	void RelDown();

	void PresParry();
	void RelParry();

	void PresCounter();
	void RelCounter();

	void PresDodge();
	void RelDodge();

//Misc

	void Damage(int val);

private:

	int energy;
	int energyMax;

	bool left;
	bool right;
	bool up;
	bool down;

	bool parry;
	bool counter;
	bool dodge;

	bool canDodge;
	int dodgeLimit;
	int dodgeCount;

	float inputDelay;
	float inputTime;
};
#endif // PLAYERCHARACTER_H

