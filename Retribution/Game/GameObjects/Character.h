#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../Engine/Rendering/GameObject.h"


/// <summary>
/// Character is designed to be the derived class of the player character
/// and all monsters in the game.  It contains universal functions like 
/// movement, the health variable, and it adds in the physics component (the image is ment
/// to be included in the derived class itself)
/// </summary>
class Character : public GameObject {
public:
	Character(glm::vec2 position_, float depth_);
	virtual ~Character();


	virtual bool OnCreate();
	virtual void Update(const float deltaTime_) override;

	//Getters

	int GetHealth() const;
	int GetMaxHealth() const;

	//returns false if facing right, true if facing right.
	bool GetDirFaceing() const;


	//Setters

	void SetHealth(const int health_);
	void SetMaxHealth(const int health_);

	void Flip(bool flip_);

	void Damage(int value);

private:
	int health;
	int maxHealth;


	//Has the object been fliped? false is right, true is left.
	bool flip;
};


#endif // !CHARACTER_H

