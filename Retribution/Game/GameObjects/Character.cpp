#include "Character.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Rendering/SceneGraph.h"


Character::Character(glm::vec2 position_, const float depth_) : GameObject(position_, depth_), 
health(0), maxHealth(0), flip(false)
{

}

Character::~Character()
{
	SceneGraph::GetInstance()->RemoveImage(GetComponent<Image>()->GetImageLoc(), ShaderHandler::GetInstance()->GetShader("BasicShader"));
}

bool Character::OnCreate()
{
	AddComponent<Physics2D>(this);

	GetComponent<Physics2D>()->SetRigidBody(true);
	GetComponent<Physics2D>()->ApplyGravity(true);

	AddCollisionTag("Tile");

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

void Character::Flip(bool flip_)
{
	if (flip != flip_) {
		GetComponent<Image>()->Flip(flip_);
		flip = flip_;
	}
}

void Character::Damage(int value)
{
	health = health - value;
}
