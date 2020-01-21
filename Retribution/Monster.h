#pragma once
#include "Character.h"

class GameScene;

class Monster : public Character
{
public:
	Monster(GameScene* pro);
	virtual ~Monster();


	virtual void Update(const float deltaTime);

	virtual void Jump();

	int dir;

	//Projectiles
	GameScene* proPtr;

	float delay;
};

