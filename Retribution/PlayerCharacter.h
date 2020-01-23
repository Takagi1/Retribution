#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "Character.h"

class GameScene;

class PlayerCharacter : public Character
{

public:
	PlayerCharacter(GameScene* scene);
	virtual ~PlayerCharacter();

	int energy;

	bool idle;

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

//Misc

	void Damage(int val);

private:

	bool left;
	bool right;
	bool up;
	bool down;

	bool parry;
	bool counter;

	
};
#endif // PLAYERCHARACTER_H

