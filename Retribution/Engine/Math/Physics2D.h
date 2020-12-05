#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include "../Rendering/Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>


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

	void ApplyDrag(bool state_);

//Section for Collision

	void CollisionResponse(std::weak_ptr<GameObject> obj, const float deltaTime_);

private:

	glm::vec2 velocity, acceleration, gravity;

	float torque, mass, rotationalInertia, angularVel, angularAcc;

	bool rigidBody; //Does the object have collision with other objects of rigidBody?

	bool staticObj; //Skips the update function

	glm::vec2 drag;

	bool applyDrag;

	void Drag();

	//Non used 

	bool FindContainingPoint() override;
	void Draw() override;

};
#endif // !PHYSICS2D_H