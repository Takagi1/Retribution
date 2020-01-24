#ifndef CHARACTER_H
#define CHARACTER_H

#include "AnimationController.h"

class GameScene;

class Character
{
public:

	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);

	AnimationController animationController;
	sf::RectangleShape body;

	int health;

// Movement
	
	float xSpeed;
	float ySpeed;

	bool onGround;

	bool isInv;
	float invTime;

	bool Collision(sf::FloatRect colid);

protected:
	GameScene* scene;

	bool isDead;

	int xDir;
};
#endif // !CHARACTER_H

