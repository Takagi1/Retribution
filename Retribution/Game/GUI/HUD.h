#ifndef HUD_H
#define HUD_H

#include "HUD Objects/HealthBar.h"
#include "HUD Objects/EnergyBar.h"

/*
Used to hold and update all GUI objects
*/

class HUD
{
public:
	HUD();
	~HUD();

	//Create's and adds all the hud elements to the SceneGraph as well

	//TODO: finish

	//1. How do the components here get info
	//2. When player takes damage update health
	//3. When player gets energy update energy
	bool OnCreate();
	void Update(const float deltaTime_);

	void UpdateHealth(int health_);

private:
	
	HealthBar healthBar;
};
#endif // !HUD_H
