#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
#include "CounterBox.h"

class GameScene;

class PlayerCharacter : public Character
{

public:
	PlayerCharacter(GameScene* scene);
	virtual ~PlayerCharacter();

	void Update(const float deltaTime);

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

	void PresAlt();
	void RelAlt();

//COUNTER BOX 

	std::unique_ptr<CounterBox> counterbox;

	void SetBlock(bool blocking);
	void Vulnerable(float time_);
	void SetCross(bool value);

//Misc

	void SetMaxHealth(int val);

	void SetHealth(int val);
	void TakeDamage(int val);

	void AddEnergy(int value);
	int UseEnergy();

	void AddGold(int value);
	bool RemoveGold(int value);

	//Reset Character to normal state
	void Neutral();

//Static value Returns

	static int GetHealth();
	static int GetEnergy();
	static int GetGold();

private:

	static int health;
	static int maxHealth;

	static int energy;
	static int energyMax;

	static int gold;

	static int dodgeLimit;

	bool isBlocking;

	bool left;
	bool right;
	bool up;
	bool down;

	bool parry;
	bool counter;
	bool dodge;
	bool alt;

	bool canDodge;
	int dodgeCount;

	float inputDelay;
	float inputTime;

	float walkSpeed;
	float dodgeSpeed;

	void Dodge(int x_, int y_);

	void Action(int x_, int y_);

	bool isVulnerable;
	float vulnerableTime;

	bool cross;
};
#endif // PLAYERCHARACTER_H

