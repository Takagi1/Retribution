#include "Physics2D.h"
#include "../Rendering/GameObject.h"


Physics2D::Physics2D() : Component(), torque(0),rotationalInertia(0),mass(0),
applyGravity(false),angularVel(0),angularAcc(0){

}

Physics2D::~Physics2D() {

}

bool Physics2D::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void Physics2D::Update(const float deltaTime_)
{

	/*
	First rotate 
	*/

	//Step 4. orientation
	parent->SetAngle(parent->GetAngle() + angularVel * deltaTime_ + 0.5f * angularAcc * pow(deltaTime_, 2));

	//Step 3. angle velocity
	angularVel += angularAcc * deltaTime_;

	/*
	Move object
	*/

	//Step 5.
	//acceleration = (glm::mat2(cos(parent->GetAngle()), -sin(parent->GetAngle()), sin(parent->GetAngle()), cos(parent->GetAngle())) * force) / mass;

	//Step 6. Find liniar acceleration vector in world space
	//forward_thrust_world = acceleration * mass;

	//Step 8. Calculate new position

	parent->SetPosition(parent->GetPosition() + glm::vec2(velocity * deltaTime_ + acceleration / 2.0f * pow(deltaTime_, 2)));

	//Step 7. Find velocity vector
	velocity += acceleration * deltaTime_;
}

glm::vec2 Physics2D::GetVelocity() const
{
	return velocity;
}

glm::vec2 Physics2D::GetAcceleration() const
{
	return acceleration;
}

float Physics2D::GetTorque() const
{
	return torque;
}

void Physics2D::SetVelocity(glm::vec2 velocity_)
{
	velocity = velocity_;
}

void Physics2D::SetAcceleration(glm::vec2 acceleration_)
{
	acceleration = acceleration_;
}

void Physics2D::SetTorque(float torque_)
{
	torque = torque_;

	angularAcc = torque / rotationalInertia;
}

void Physics2D::SetForce(glm::vec2 force_)
{
	force = force_;

	//apply force relative to direction. Is this wrong?
	acceleration = glm::mat2(cos(parent->GetAngle()), -sin(parent->GetAngle()), sin(parent->GetAngle()), cos(parent->GetAngle())) * force / mass;
}

void Physics2D::ApplyGravity(bool state_)
{
	applyGravity = state_;
}
