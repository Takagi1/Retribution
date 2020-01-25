#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
public:
	Animation();
	~Animation();

	virtual void Update(const float deltaTime_, sf::RectangleShape* body) = 0;
	
	float totalTime;
	float maxTime;

};

#endif // !ANIMATION_H
