#pragma once

#include "../../../Engine/Rendering/GameObject.h"

class EnergyBar : public GameObject {
public:
	EnergyBar(glm::vec2 position_ = glm::vec2());
	virtual ~EnergyBar();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	void UpdateHealth(int health_);

	void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) override;
private:
	
};
