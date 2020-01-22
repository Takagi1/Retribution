#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H
#include "Character.h"

class GameScene;
class TestCharacter : public Character
{

public:
	TestCharacter(GameScene* scene);
	virtual ~TestCharacter();

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

//Misc

	void Damage(int val);

	int dx = 0;
	int dy = 0;

private:

	bool left;
	bool right;
	bool up;
	bool down;

	bool parry;
	bool counter;

	
};
#endif // TESTCHARACTER_H

