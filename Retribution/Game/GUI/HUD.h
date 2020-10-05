#ifndef HUD_H
#define HUD_H

#include "HUD Objects/HealthBar.h"

/*
Used to hold and update all GUI objects
*/

class HUD
{
public:
	HUD();
	~HUD();

	//Create's and adds all the hud elements to the SceneGraph as well
	bool OnCreate();
	void Update(const float deltaTime_);

	void UpdateHealth(int health_);

private:
	
	HealthBar healthBar;
};
#endif // !HUD_H
