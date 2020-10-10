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

	int GetHealth() const ;

	void SetHealth(const int health_);

	//Takes in input?
	void Dash(int horizontal_, int vertical_);

	void CollisionResponse(std::vector<GameObject*> obj_) override;

	//-1 is left, 1 is right
	void Move(int direction_);

private:
	static int health;
	static int maxHealth;
};
#endif // !PLAYERCHARACTER_H
