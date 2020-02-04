#pragma once
#include "../Animation.h"
class MonsterIdle :
	public Animation
{
public:
	MonsterIdle();
	~MonsterIdle();

	virtual void Update(const float deltaTime_, Character* character_);

	virtual void EndAnimation(Character* character_);

};

