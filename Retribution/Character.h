#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game/Animation/AnimationController.h"

class GameScene;

class Character
{
public:

	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);

	std::unique_ptr<AnimationController> animationController;
	sf::RectangleShape body;
	std::unordered_map<std::string, bool> animationState;

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
};
#endif // !CHARACTER_H

