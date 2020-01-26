#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "Animation.h"
#include <map>

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	//Reference to characters body
	Character* character;

	std::map<std::string, Animation*> animationList;

	Animation * currentAnimation;

	void Update(const float deltaTime_);

	//Put in a name to play that animation
	void Play(std::string name_);

};

#endif // !ANIMATIONCONTROLLER_H