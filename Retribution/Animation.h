#pragma once

class Animation
{
public:
	Animation();
	~Animation();

	virtual void Update(const float deltaTime_, sf::RectangleShape* body) = 0;
	
	float totalTime;
	float maxTime;

};

