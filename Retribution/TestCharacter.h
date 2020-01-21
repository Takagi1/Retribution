#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H
#include "Character.h"

class TestCharacter : public Character
{

public:
	TestCharacter();
	virtual ~TestCharacter();

	bool idle;

	void Update(const float deltaTime);

	void Jump();
	
	int energy;
};
#endif // TESTCHARACTER_H

