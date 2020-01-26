#ifndef ANIMATION_H
#define ANIMATION_H

class Character;

class Animation
{
public:
	Animation();
	~Animation();

	virtual void Update(const float deltaTime_, Character* body) = 0;
	
	virtual void EndAnimation(Character* character) = 0;
	float totalTime;
	float maxTime;

};

#endif // !ANIMATION_H
