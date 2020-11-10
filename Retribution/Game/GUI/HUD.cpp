#include "HUD.h"
#include "../../Engine/Rendering/SceneGraph.h"


HUD::HUD() 
{

}

HUD::~HUD()
{
}

bool HUD::OnCreate()
{
	healthBar.OnCreate();
	SceneGraph::GetInstance()->AddGUIObject(&healthBar, "HealthBar");

	energyBar.OnCreate();

	return true;
}

void HUD::Update(const float deltaTime_)
{
}

void HUD::UpdateHealth(int health_)
{
	healthBar.UpdateHealth(health_);
}

void HUD::UpdateEnergy(int energy_)
{
	energyBar.UpdateEnergy(energy_);
}
