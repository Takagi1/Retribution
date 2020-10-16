#include "PlayerCharacter.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Math/BoundingBox.h"

PlayerCharacter::PlayerCharacter(glm::vec2 position_) : Character(position_,0), energy(0), maxEnergy(0),
pState(State::Neutral), triggerBox(nullptr)
{

}


PlayerCharacter::~PlayerCharacter()
{
}

bool PlayerCharacter::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario.png", true);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

	SetDepth(1);
	SetScale(glm::vec2(0.1f,0.1f));

	SetHealth(5);

	return true;
}

void PlayerCharacter::Update(const float deltaTime_)
{
	if (triggerBox) {
		triggerBox->Update();
	}

	if (lifeTime > 0) {
		lifeTime -= deltaTime_;
		if (lifeTime < 0) {
			lifeTime = 0;
			pState = State::Neutral;
		}
	}

	Character::Update(deltaTime_);
}

/*
void PlayerCharacter::Dash(int horizontal_, int vertical_)
{
	
}
*/

//This might be realllllly dirty
void PlayerCharacter::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{

}

void PlayerCharacter::Parry(const bool isRight_)
{
	//TODO: This is temp as it needs to be seriously improved

	//TODO: create method of suspending player actions

	//Step 1. Create box
	triggerBox = new TriggerBox(this, parryType, glm::vec2(100.0f, GetBoundingBox().dimentions.y), 
		glm::vec2(GetPosition().x + (isRight_ ? GetBoundingBox().dimentions.x : 0), GetPosition().y));

	pState = State::Action;

	lifeTime = 1.5f;
}

int PlayerCharacter::GetEnergy() const
{
	return energy;
}

std::string PlayerCharacter::GetParryType() const
{
	return parryType;
}

std::string PlayerCharacter::GetCounterType() const
{
	return counterType;
}

State PlayerCharacter::GetState() const
{
	return pState;
}

void PlayerCharacter::SetEnergy(const int energy_)
{
	if (energy_ <= 0) {
		energy = 0;
	}
	else if (energy_ >= maxEnergy) {
		energy = maxEnergy;
	}
	else {
		energy = energy_;
	}
}

void PlayerCharacter::SetParryType(const std::string parry_)
{
	parryType = parry_;
}

void PlayerCharacter::SetCounterType(const std::string counter_)
{
	counterType = counter_;
}

void PlayerCharacter::ChangeEnergy(const int energy_)
{
	energy += energy_;

	if (energy < 0) { energy = 0; }
	if (energy > maxEnergy) { energy = maxEnergy; }
}
