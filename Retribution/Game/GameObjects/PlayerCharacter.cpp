#include "PlayerCharacter.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Math/BoundingBox.h"

PlayerCharacter::PlayerCharacter(glm::vec2 position_) : Character(position_,0), energy(0), maxEnergy(0),
pState(State::Neutral), triggerBox(nullptr), parryType(TriggerType::Parry), counterType(TriggerType::Counter),
lifeTime(0), energyLevel(1)
{

}


PlayerCharacter::~PlayerCharacter()
{
	
}

bool PlayerCharacter::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario3.png", 0.0f);

	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

	GetComponent<Physics2D>()->ApplyDrag(true);

	SetTag("Player");

	//SetDepth(1);
	SetScale(glm::vec2(0.1f,0.1f));

	SetMaxHealth(3);
	SetHealth(3);
	maxEnergy = 10;

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
			delete triggerBox;
			triggerBox = nullptr;
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
	GameObject::CollisionResponse(obj_);
}

void PlayerCharacter::Parry()
{
	//Step 1. Create box
	triggerBox = new TriggerBox(this, parryType, glm::vec2(50.0f, GetBoundingBox().dimentions.y * 2.0f), 
		glm::vec2(GetPosition().x + (GetDirFaceing() ?  -60.0f : GetBoundingBox().dimentions.x), GetPosition().y));

	pState = State::Action;

	lifeTime = 1.5f;
}

void PlayerCharacter::Counter()
{
	//Step 1. Create box
	triggerBox = new TriggerBox(this, counterType, glm::vec2(50.0f, GetBoundingBox().dimentions.y * 2.0f),
		glm::vec2(GetPosition().x + (GetDirFaceing() ? -60.0f : GetBoundingBox().dimentions.x), GetPosition().y));

	pState = State::Action;

	lifeTime = 1.5f;
}

int PlayerCharacter::GetEnergy() const
{
	return energy;
}

TriggerType PlayerCharacter::GetParryType() const
{
	return parryType;
}

TriggerType PlayerCharacter::GetCounterType() const
{
	return counterType;
}

State PlayerCharacter::GetState() const
{
	return pState;
}

int PlayerCharacter::GetEnergyLevel() const
{
	return energyLevel;
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

void PlayerCharacter::SetParryType(const TriggerType parry_)
{
	parryType = parry_;
}

void PlayerCharacter::SetCounterType(const TriggerType counter_)
{
	counterType = counter_;
}

void PlayerCharacter::SetState(State state)
{
	pState = state;
}

void PlayerCharacter::ChangeEnergy(const int energy_)
{
	energy += energy_;
	if (energy > energyLevel * 5) { energyLevel++; }

	SetEnergy(energy);
}

void PlayerCharacter::ResetEnergy()
{
	energy = 0;
	energyLevel = 1;
}

//TODO: create speed limit or create something that will stop the character from moving to qickly

void PlayerCharacter::Move(int directionX_, int directionY_)
{
	//TODO: move speed?
	GetComponent<Physics2D>()->SetVelocity(glm::vec2(40.0f * directionX_, 0 * directionY_));

	//flip object to direction it needs to face

	if (directionX_ == 1.0f) {
		Flip(false);
	}
	else if (directionX_ == -1.0f) {
		Flip(true);
	}
}