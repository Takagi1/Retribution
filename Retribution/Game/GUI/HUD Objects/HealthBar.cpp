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
	GetComponent<GUIImage>()->OnCreate("Red.png");


	SetPosition(glm::vec2(200.0f, 200.0f));
	SetScale(glm::vec2(10.0f, 5.0f));

	return true;
}

void HealthBar::Update(const float deltaTime_)
{
}

void HealthBar::UpdateHealth(int health_)
{
	health = health_;
	SetScale(glm::vec2(10.0f, 5.0f * health_));
}