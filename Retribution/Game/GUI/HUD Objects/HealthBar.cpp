#include "HealthBar.h"
#include "../../../Engine/Rendering/GUI/GUIImage.h"

HealthBar::HealthBar(glm::vec2 position_) : GUIObject(position_), health(1) {

}

HealthBar::~HealthBar()
{
}

bool HealthBar::OnCreate()
{
	AddComponent<GUIImage>(this);

	//GetComponent<Image>()->OnCreate(this);
	GetComponent<GUIImage>()->OnCreate("Mario2.png");


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