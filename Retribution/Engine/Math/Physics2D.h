#pragma once

#include "../Rendering/Component.h"
#include <glm/glm.hpp>


class GameObject;

class Physics2D : public Component {
public:
	Physics2D(GameObject* parent_);
	virtual ~Physics2D();

	void Update(const float deltaTime_) override;

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

//Section for Collision

	//TODO: optional: create ray and implement this
	void ContinuousDetection();

	void DiscreteDetection();

private:

	glm::vec2 velocity, acceleration, forward_thrust_space, forward_thrust_world, force;

	float torque, mass, rotationalInertia, angularVel, angularAcc, gravity;


	//Non used 

	bool FindContainingPoint() override;
	void Draw(Camera* camera) override;

};