#pragma once

#include "../Rendering/Component.h"
#include <glm/glm.hpp>

class GameObject;

class Physics2D : public Component {
public:
	Physics2D();
	virtual ~Physics2D();

	virtual bool OnCreate(GameObject* parent_) override;
	virtual void Update(const float deltaTime_) override;

	//Getters 
	glm::vec2 GetVelocity() const;
	glm::vec2 GetAcceleration() const;
	float GetTorque() const;

	//Setters
	void SetVelocity(glm::vec2 velocity_);
	void SetAcceleration(glm::vec2 acceleration_);
	void SetTorque(float torque_);
	void SetForce(glm::vec2 force_);

	//Apply gravity to object
	void ApplyGravity(bool state_);

private:
	bool applyGravity;

	glm::vec2 velocity, acceleration, forward_thrust_space, forward_thrust_world, force;

	float torque, mass, rotationalInertia, angularVel, angularAcc;

};