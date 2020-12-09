#include "EnergyDisplay.h"
#include "../../../Engine/Rendering/SceneGraph.h"

EnergyDisplay::EnergyDisplay(glm::vec2 position)
{

}

EnergyDisplay::~EnergyDisplay()
{

//TODO: Remove GUI Objects

}

bool EnergyDisplay::OnCreate()
{
	bars.reserve(3);

	bars.push_back(EnergyBar(glm::vec2(0,200)));

	bars[0].OnCreate();

	AddBar(&bars[0]);


	return true;
}

void EnergyDisplay::Update(const float deltaTime_)
{

}

void EnergyDisplay::UpdateEnergy(int value_)
{
	int i = 0;
	for (; value_ > 0; i++) {
		bars[i].UpdateEnergy(value_ > 10 ? 10 : value_);
		value_ -= 10;
	}

	for (; i < bars.size(); i++) {
		bars[i].UpdateEnergy(0);
	}
}

void EnergyDisplay::AddBar(EnergyBar* bar)
{
	SceneGraph::GetInstance()->AddGUIObject(bar, "EnergyBar");
}
