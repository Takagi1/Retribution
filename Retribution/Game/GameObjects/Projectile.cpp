#include "Projectile.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Game/GameObjects/PlayerCharacter.h"

Projectile::Projectile(Character* parent_, glm::vec2 position_, const float depth_) :GameObject(position_, depth_), 
power(0), isFliped(false), speed(0)
{
	parent = parent_;

}

Projectile::~Projectile()
{
	SceneGraph::GetInstance()->RemoveImage(GetComponent<Image>()->GetImageLoc(), ShaderHandler::GetInstance()->GetShader("BasicShader"));
	parent = nullptr;
}

bool Projectile::OnCreate(bool isFliped_)
{
	AddComponent<Physics2D>(this);
	isFliped = isFliped_;

	SetTag("Projectile");
	AddCollisionTag("Player");

	if (isFliped) {
		SetScale(GetScale() * -1.0f);
	}

	return true;
}

void Projectile::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}

void Projectile::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
	for (auto o : obj_) {
		if (o.lock()->GetTag() == "Player") {
			//TODO: Damage Player
			dynamic_cast<PlayerCharacter*>(o.lock().get())->Damage(power);
			dynamic_cast<PlayerCharacter*>(o.lock().get())->ResetEnergy();


			//TODO: Destroy Projectile
			SceneGraph::GetInstance()->RemoveGameObject(GetName());
			return;
		}
	}
	GameObject::CollisionResponse(obj_);
}

int Projectile::GetPower() const
{
	return power;
}

float Projectile::GetSpeed() const
{
	return speed;
}

void Projectile::SetPower(const int power_)
{
	power = power_;
}

void Projectile::SetSpeed(const float speed_)
{
	speed = speed_;
	GetComponent<Physics2D>()->SetVelocity(glm::vec2(speed * (isFliped ? -1 : 1), 0));
}

void Projectile::DamageParent(int damage_)
{
	parent->Damage(damage_ + power);
}
