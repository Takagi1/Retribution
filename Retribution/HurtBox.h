#pragma once

class GameObject;

class HurtBox
{
public:
	HurtBox();
	~HurtBox();

	void SetObject(GameObject* obj_);
	GameObject* GetGameObject() const;

	void SetPosition(sf::Vector2f pos_);
	void SetPosition(float x_, float y_);

	sf::Vector2f GetPosition() const ;

	void SetSize(sf::Vector2f size_);
	void SetSize(float x, float y);

	sf::Vector2f GetSize() const;

	void SetFillColour(sf::Color colour_);

	void Move(sf::Vector2f pos_);
	void Move(float x_, float y_);

	bool Collision(sf::FloatRect colid_);
	sf::FloatRect GetCollider() const;
	
	sf::RectangleShape Draw() const;



private:

	sf::RectangleShape box;

	GameObject* obj;
	
};

