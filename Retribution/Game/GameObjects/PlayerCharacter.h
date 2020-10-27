#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
#include "../Scripts/TriggerBox.h"

enum class State {
	Neutral,
	Action
};

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(glm::vec2 position_ = glm::vec2());
	virtual ~PlayerCharacter();


	virtual bool OnCreate();
	virtual void Update(const float deltaTime_) override;

	void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) override;

	//Takes in input?
	//void Dash(int horizontal_, int vertical_); might not do dash for now

	void Parry();

	void Counter();


	//Getters

	int GetEnergy() const;
	std::string GetParryType() const;
	std::string GetCounterType() const;
	State GetState() const;

	//Setters

	void SetEnergy(const int energy_); //Use to set energy to a specific amount
	void SetParryType(const std::string parry_);
	void SetCounterType(const std::string counter_);
	
	void ChangeEnergy(const int energy_);//Use to add or subtract from energy

private:
	int energy;
	int maxEnergy;

	TriggerBox* triggerBox;
	float lifeTime;

	//TODO: add in check to prevent invalid strings from being set

	std::string counterType;
	std::string parryType;



	State pState;

};
#endif // !PLAYERCHARACTER_H
