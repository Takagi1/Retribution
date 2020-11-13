#include "EnergyDisplay.h"
#include "../../../Engine/Rendering/SceneGraph.h"

EnergyDisplay::EnergyDisplay(glm::vec2 position)
{

}

EnergyDisplay::~EnergyDisplay()
{

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
	float trans = value_;
	float res = trans / 10.0f;
	int full = std::floor(res);
	float remaining = res - full;

	int rounding = std::floor(remaining * 10.0f);

	for (int i = 0; i < full; i++) {
		bars[i].UpdateEnergy(10);
	}
	if (rounding > 0) {
		bars[full].UpdateEnergy(rounding);
	}
}

void EnergyDisplay::AddBar(EnergyBar* bar)
{
	SceneGraph::GetInstance()->AddGUIObject(bar, "EnergyBar");
}
