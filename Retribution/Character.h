#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game/Animation/AnimationController.h"
#include "Engine/Rendering/2D/GameObject.h"

class GameScene;

class Character : public GameObject
{
public:

	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);

	virtual void TakeDamage(int val) = 0;

	std::unique_ptr<AnimationController> animationController;

// Movement
	
	float xSpeed;
	float ySpeed;

	float invTime;

	bool GetInv() const;
	bool GetDead() const;

	void SetInv(bool stat_);
	void SetDead(bool death);

protected:
	GameScene* scene;

	bool onGround;

private:
	bool inv;
	bool isDead;
};
#endif // !CHARACTER_H

