#include "HealthBar.h"
#include "../../../Engine/Rendering/Types/Image.h"

HealthBar::HealthBar(glm::vec2 position_) : GameObject(position_, 0), health(1) {

}

HealthBar::~HealthBar()
{
}

bool HealthBar::OnCreate()
{
	AddComponent<Image>();

	GetComponent<Image>()->OnCreate(this);
	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("GUIShader"), "Mario2", false);


	SetPosition(glm::vec2(10.0f, 100.0f));
	SetScale(glm::vec2(100.0f, 100.0f));

	return true;
}

void HealthBar::Update(const float deltaTime_)
{
}

void HealthBar::UpdateHealth(int health_)
{
	health = health_;
}
