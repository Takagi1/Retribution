#pragma once
#include "EnergyBar.h"

//It is a holder for energy bars that will determine how they are displayed.
class EnergyDisplay {
public:
	EnergyDisplay(glm::vec2 position = glm::vec2(0));
	~EnergyDisplay();

	bool OnCreate();

	virtual void Update(const float deltaTime_);

	void UpdateEnergy(int value_);

	void AddBar(EnergyBar* bar);

private:
	std::vector<EnergyBar> bars;

};