#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game/Animation/AnimationController.h"
#include "GameObject.h"

class GameScene;

class Character : public GameObject
{
public:

	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);

	std::unique_ptr<AnimationController> animationController;
	std::unordered_map<std::string, bool> animationState;

	int health;

// Movement
	
	float xSpeed;
	float ySpeed;

	bool onGround;

	float invTime;

	void SetInv(bool stat_);
	bool GetInv();

	bool Collision(sf::FloatRect colid);

protected:
	bool inv;
	GameScene* scene;

	bool isDead;
};
#endif // !CHARACTER_H

