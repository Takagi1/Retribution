#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include "../Rendering/Component.h"
#include <glm/glm.hpp>
#include <vector>


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
	bool GetRigidBody() const;
	bool GetStaticObj() const;

	//Setters
	
	void SetVelocity(glm::vec2 velocity_);
	void SetAcceleration(glm::vec2 acceleration_);
	void SetTorque(float torque_);
	void ApplyForce(glm::vec2 force_);
	void SetRigidBody(const bool body_);
	void SetStaticObj(const bool type_);

	//Apply gravity to object
	void ApplyGravity(bool state_);

//Section for Collision

	void CollisionResponse(std::vector<GameObject*> obj, const float deltaTime_);

private:

	glm::vec2 velocity, acceleration, forward_thrust_space, forward_thrust_world;

	float torque, mass, rotationalInertia, angularVel, angularAcc, gravity;

	bool rigidBody;
	bool staticObj;

	glm::vec2 drag;


	//Non used 

	bool FindContainingPoint() override;
	void Draw(Camera* camera) override;

};
#endif // !PHYSICS2D_H