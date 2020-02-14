#pragma once

class Monster;

class Projectile
{
public:
	Projectile(sf::Vector2f pos_, sf::Vector2f angle_, Monster* caster);
	~Projectile();

	void Update(const float deltaTime);

	bool Collision(sf::FloatRect ground_);

	sf::RectangleShape box;

	Monster* caster;

	sf::Vector2f angle;
	int power;
	bool isBlocked;
	
};

