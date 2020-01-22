#pragma once

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Update(const float deltaTime);
	sf::RectangleShape body;

	int health;

// Movement
	int xDir;

	float xSpeed;
	float ySpeed;

	bool onGround;
	bool jump;

	bool isInv;
	float invTime;

	virtual void Jump();

	bool Collision(sf::FloatRect colid);

};

