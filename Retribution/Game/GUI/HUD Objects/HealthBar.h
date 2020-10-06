#pragma once
#include "../../../Engine/Rendering/GameObject.h"

class HealthBar : public GameObject {
public:
	HealthBar(glm::vec2 position_ = glm::vec2());
	virtual ~HealthBar();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	void UpdateHealth(int health_);

	void CollisionResponse(std::vector<GameObject*> obj_) override;
private:
	int health;
};

