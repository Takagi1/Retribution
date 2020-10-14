#include "PlayerCharacter.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Math/BoundingBox.h"

PlayerCharacter::PlayerCharacter(glm::vec2 position_) : Character(position_,0), energy(0), maxEnergy(0)
{

}


PlayerCharacter::~PlayerCharacter()
{
}

bool PlayerCharacter::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	//GetComponent<Image>()->OnCreate(this);
	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario", true);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

	SetPosition(glm::vec2(10.0f, 10.0f));
	SetDepth(1);
	SetScale(glm::vec2(0.1f,0.1f));

	SetHealth(5);

	return true;
}

void PlayerCharacter::Update(const float deltaTime_)
{
	Character::Update(deltaTime_);


	//TODO:Should i have a check here to see if image is added or would that be redundant 
//because it should not get here if image is not added?

	//null the obj
}

/*
void PlayerCharacter::Dash(int horizontal_, int vertical_)
{
	
}
*/

//This might be realllllly dirty
void PlayerCharacter::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
	//Clean the end
	
	//TODO: note it seems here on the first frame that both objects hit twise?
	//if (obj_.size() != 0) {
	//	for (int i = 0; obj_.size() != 0;) {
	//		//obj_[i] = nullptr;
	//		obj_.erase(obj_.begin() + i);
	//	}
	//}

}

void PlayerCharacter::Parry()
{
	//TODO: Decide if it should be a seperate class or not
	
	//for now the idea is that when the box is created the 
	//it should be added into the collision response
	//so that the game will do a collision check with it?
	
	//Then there will be checks to see if it collides with 
	//an attack. collision response has been planned out
	//so you should know it already.
}

int PlayerCharacter::GetEnergy() const
{
	return energy;
}

void PlayerCharacter::ChangeEnergy(const int energy_)
{
	energy += energy_;

	if (energy < 0) { energy = 0; }
	if (energy > maxEnergy) { energy = maxEnergy; }
}
