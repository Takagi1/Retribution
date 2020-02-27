#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game/Animation/AnimationController.h"
#include "Engine/GameObject.h"

class GameScene;

class Character : public GameObject
{
public:

	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);

	virtual void TakeDamage(int val) = 0;

	std::unique_ptr<AnimationController> animationController;
	std::unordered_map<std::string, bool> animationState;

// Movement
	
	float xSpeed;
	float ySpeed;

	bool onGround;

	float invTime;

	bool GetInv() const;
	bool GetDead() const;

	void SetInv(bool stat_);
	void SetDead(bool death);

protected:
	GameScene* scene;
private:
	int maxHealth;

	bool inv;
	bool isDead;
};
#endif // !CHARACTER_H

