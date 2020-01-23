#pragma once

class GameScene;

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

	bool isInv;
	float invTime;

	bool Collision(sf::FloatRect colid);

protected:
	GameScene* scene;

	bool jump;
	bool isDead;

};

