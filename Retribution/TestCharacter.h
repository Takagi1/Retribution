#pragma once


class TestCharacter
{

public:
	TestCharacter();
	~TestCharacter();

	sf::RectangleShape body;

	int xDir;

	float xSpeed;
	float ySpeed;

	bool onGround;

	bool idle;

	void Update(const float deltaTime);

	void Jump();
	
};

