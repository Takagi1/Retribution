#pragma once

class Character
{
public:
	Character();
	virtual ~Character();

	int xDir;

	float xSpeed;
	float ySpeed;

	bool onGround;
	bool jump;

	virtual void Update(const float deltaTime);

	virtual void Jump();

	sf::RectangleShape body;
};

