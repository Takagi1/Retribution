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


	return true;
}

void HUD::Update(const float deltaTime_)
{
}

void HUD::UpdateHealth(int health_)
{
	healthBar.UpdateHealth(health_);
}
