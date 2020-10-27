#include "Physics2D.h"
#include "../Rendering/GameObject.h"



#define Gravity 9.8f

Physics2D::Physics2D(GameObject* parent_) : Component(), torque(0),rotationalInertia(0),mass(0),
gravity(0.0f),angularVel(0),angularAcc(0), staticObj(false), rigidBody(false), drag(1), applyDrag(false)
{

	parent = parent_;
}

Physics2D::~Physics2D() {

}

void Physics2D::Update(const float deltaTime_)
{

	/*
	First rotate 
	*/
	if (!staticObj) {
		//Step 4. orientation
		parent->Rotate(angularVel * deltaTime_ + 0.5f * angularAcc * pow(deltaTime_, 2));

		//Step 3. angle velocity
		angularVel += angularAcc * deltaTime_;

		/*
		Move object
		*/

		parent->Translate(glm::vec2(velocity * deltaTime_ + acceleration / 2.0f * pow(deltaTime_, 2)));


		//Step 7. Find velocity vector
		velocity += acceleration * deltaTime_;

		if (applyDrag) { Drag(); }

	}
}


void Physics2D::Draw()
{
}

bool Physics2D::FindContainingPoint()
{
	return false;
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

bool Physics2D::GetRigidBody() const
{
	return rigidBody;
}

bool Physics2D::GetStaticObj() const
{
	return staticObj;
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

void Physics2D::ApplyForce(glm::vec2 force_)
{
	//apply force relative to direction. Is this wrong?
	acceleration = glm::mat2(cos(parent->GetAngle()), -sin(parent->GetAngle()), sin(parent->GetAngle()), cos(parent->GetAngle())) * force_;

	if (mass != 0) {
		acceleration /= mass;
	}
}


void Physics2D::SetRigidBody(const bool body_)
{
	rigidBody = body_;
}

void Physics2D::SetStaticObj(const bool type_)
{
	staticObj = type_;
}

void Physics2D::ApplyGravity(bool state_)
{
	if (state_) {
		gravity = Gravity;
	}
	else {
		gravity = 0.0f;
	}
}

void Physics2D::ApplyDrag(bool state_)
{
	applyDrag = state_;
}

//TODO: Apply drag to slow down the object (this is TODO because i dont know if this method sucks or not.
void Physics2D::Drag()
{
	if (velocity.x > 0) {
		if (velocity.x <= drag.x) { velocity.x = 0; }
		else { velocity.x -= drag.x; }
	}
	else if (velocity.x < 0) {
		if (velocity.x >= -drag.x) { velocity.x = 0; }
		else { velocity.x += drag.x; }
	}

	if (velocity.y > 0) {
		if (velocity.y <= drag.y) { velocity.y = 0; }
		else { velocity.y -= drag.y; }
	}
	else if (velocity.y < 0) {
		if (velocity.y >= -drag.y) { velocity.y = 0; }
		else { velocity.y += drag.y; }
	}
}

//This function is designed to push two objects that are colliding appart.
void Physics2D::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj, const float deltaTime_)
{
	for (auto o : obj) {
		if (o.lock()->GetName() != parent->GetName()) {
			Physics2D* physics = o.lock()->GetComponent<Physics2D>();
			if (physics) {
				if (physics->GetRigidBody()) {
					glm::vec2 depth = parent->GetBoundingBox().CollisionDepth(&o.lock()->GetBoundingBox());

					parent->Translate(depth);
				}
				physics = nullptr;
			}
		}
	}
}
