#pragma once
#include "../../../Engine/Rendering/GUI/GUIObject.h"

class HealthBar : public GUIObject {
public:
	HealthBar(glm::vec2 position_ = glm::vec2());
	virtual ~HealthBar();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	void UpdateHealth(int health_);

private:
	int health;
};

