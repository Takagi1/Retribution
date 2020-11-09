#include "HealthBar.h"
#include "../../../Engine/Rendering/Types/Image.h"

HealthBar::HealthBar(glm::vec2 position_) : GameObject(position_, 0), health(1) {

}

HealthBar::~HealthBar()
{
}

bool HealthBar::OnCreate()
{
	AddComponent<Image>(this);

	//GetComponent<Image>()->OnCreate(this);
	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("GUIShader"), "Mario2.png", false, 0);


	SetPosition(glm::vec2(0.0f, 800.0f));
	SetScale(glm::vec2(0.1f, 0.1f));

	return true;
}

void HealthBar::Update(const float deltaTime_)
{
}

void HealthBar::UpdateHealth(int health_)
{
	health = health_;
}

void HealthBar::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
}