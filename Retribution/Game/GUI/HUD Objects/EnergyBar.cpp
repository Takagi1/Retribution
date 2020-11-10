#include "EnergyBar.h"
#include "../../../Engine/Rendering/GUI/GUIImage.h"
#include "../../../Engine/Rendering/SceneGraph.h"

EnergyBar::EnergyBar(glm::vec2 position_) : GUIObject(position_) {

}

EnergyBar::~EnergyBar() {

}

bool EnergyBar::OnCreate()
{
	AddComponent<GUIImage>(this);

	//GetComponent<Image>()->OnCreate(this);
	GetComponent<GUIImage>()->OnCreate("Blue.png");


	return true;
}

void EnergyBar::Update(const float deltaTime_)
{
}

void EnergyBar::UpdateEnergy(int energy_)
{
	SetScale(glm::vec2(10.0f, 5.0f * energy_));
}

