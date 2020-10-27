#include "Character.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/Physics2D.h"


Character::Character(glm::vec2 position_, const float depth_) : GameObject(position_, depth_), 
health(0), maxHealth(0), flip(false)
{

}

Character::~Character()
{
}

bool Character::OnCreate()
{
	AddComponent<Physics2D>(this);

	GetComponent<Physics2D>()->SetRigidBody(true);

	if (GetComponent<Physics2D>()) {
		return true;
	}
	else {
		return false;
	}
}

void Character::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}

int Character::GetHealth() const
{
	return health;
}

int Character::GetMaxHealth() const
{
	return maxHealth;
}

bool Character::GetDirFaceing() const
{
	return flip;
}

void Character::SetHealth(const int health_)
{
	health += health_;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Character::SetMaxHealth(const int health_)
{
	maxHealth = health_;
	if (health > maxHealth) {
		health = maxHealth;
	}
}
//TODO: create speed limit or create something that will stop the character from moving to qickly

void Character::Move(int directionX_, int directionY_)
{
	GetComponent<Physics2D>()->SetVelocity(glm::vec2(10.0f * directionX_, 0));

	//flip object to direction it needs to face

	if (directionX_ == 1.0f) {
		Flip(false);
	}
	else if (directionX_ == -1.0f) {
		Flip(true);
	}
}

void Character::Flip(bool flip_)
{
	if (flip != flip_) {
		GetComponent<Image>()->Flip(flip_);
		flip = flip_;
	}
}
