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

	int GetHealth() const;
	void SetHealth(int val);

	int GetMaxHealth() const;
	void SetMaxHealth(int val);

	bool GetInv() const;
	void SetInv(bool stat_);

	bool GetDead() const;
	void SetDead(bool death);


protected:
	GameScene* scene;

private:
	int health;
	int maxHealth;

	bool inv;
	bool isDead;
};
#endif // !CHARACTER_H

