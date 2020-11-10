#pragma once

#include "../../../Engine/Rendering/GUI/GUIObject.h"

class EnergyBar : public GUIObject {
public:
	EnergyBar(glm::vec2 position_ = glm::vec2());
	virtual ~EnergyBar();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	void UpdateEnergy(int energy_);
private:

};
