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

	void CollisionResponse(std::weak_ptr<GameObject> obj_) override;

	//Takes in input?
	//void Dash(int horizontal_, int vertical_); might not do dash for now

	void Parry();

	void Counter();


	//Getters

	int GetEnergy() const;
	TriggerType GetParryType() const;
	TriggerType GetCounterType() const;
	State GetState() const;
	int GetEnergyLevel() const;

	//Setters

	void SetEnergy(const int energy_); //Use to set energy to a specific amount
	void SetParryType(const TriggerType);
	void SetCounterType(const TriggerType);
	void SetState(State state);
	
	void ChangeEnergy(const int energy_);//Use to add or subtract from energy
	void ResetEnergy(); //Use to reset energy to 0.

	void Move(int directionX_, int directionY_);

private:
	int energy;
	int maxEnergy;
	int energyLevel;

	TriggerBox* triggerBox;
	float lifeTime;

	//TODO: add in check to prevent invalid strings from being set

	TriggerType counterType;
	TriggerType parryType;

	State pState;

};
#endif // !PLAYERCHARACTER_H
