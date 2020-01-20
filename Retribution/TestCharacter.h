#pragma once


class TestCharacter
{

public:
	TestCharacter();
	~TestCharacter();

	sf::RectangleShape body;

	int xDir = 0;
	int yDir = 0;

	void Update(const float deltaTime);
	
};

