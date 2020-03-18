#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "Animation.h"
#include <unordered_map>

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	//Reference to characters body
	Character* character;

	std::unordered_map<std::string, Animation*> animationList;

	Animation * currentAnimation;

	virtual void Update(const float deltaTime_) = 0;

	void SwitchAnimation(int val);

	int GetCurrentAnimationState();

protected:
	//Put in a name to play that animation
	void Play(std::string name_);

	int animationState;
	int currentAnimationState;

};

#endif // !ANIMATIONCONTROLLER_H