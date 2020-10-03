#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "../../Engine/Rendering/GameObject.h"

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter(glm::vec2 position_ = glm::vec2());
	virtual ~PlayerCharacter();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	static int health;
	static int maxHealth;

private:

};
#endif // !PLAYERCHARACTER_H
