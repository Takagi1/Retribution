#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
 

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(glm::vec2 position_ = glm::vec2());
	virtual ~PlayerCharacter();


	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);

	void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) override;

	//Takes in input?
	//void Dash(int horizontal_, int vertical_); might not do dash for now

	void Parry();

	void Counter();


	//Getters

	int GetEnergy() const;

	//Setters

	
	void SetEnergy(const int energy_); //Use to set energy to a specific amount
	
	void ChangeEnergy(const int energy_);//Use to add or subtract from energy
private:
	int energy;
	int maxEnergy;
};
#endif // !PLAYERCHARACTER_H
