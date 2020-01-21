#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H
#include "Character.h"

class GameScene;
class TestCharacter : public Character
{

public:
	TestCharacter(GameScene* scene);
	virtual ~TestCharacter();

	bool idle;

	void Update(const float deltaTime);

	void Jump();
	
	int energy;

	void Damage(int val);

	int dx = 0;
	int dy = 0;
	
	GameScene* scene;
};
#endif // TESTCHARACTER_H

