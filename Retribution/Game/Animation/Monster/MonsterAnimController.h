#pragma once
#include "../AnimationController.h"
class MonsterAnimController :
	public AnimationController
{
public:
	MonsterAnimController(Character* character_);
	~MonsterAnimController();

	virtual void Update(const float deltaTime) override;
};


