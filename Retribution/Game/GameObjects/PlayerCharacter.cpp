#include "PlayerCharacter.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/BoundingBox.h"

int PlayerCharacter::maxHealth = 5;
int PlayerCharacter::health = 5;


PlayerCharacter::PlayerCharacter(glm::vec2 position_) : GameObject(position_, 0)
{

}


PlayerCharacter::~PlayerCharacter()
{
}

bool PlayerCharacter::OnCreate()
{
	AddComponent<Image>();

	GetComponent<Image>()->OnCreate(this);
	GetComponent<Image>()->OnCreate("Mario");


	SetPosition(glm::vec2(400.0f, 300.0f));
	SetScale(glm::vec2(100.0f,100.0f));

	health = 5;

	//GetComponent<Physics3D>()->SetMass(1);
	//SceneGraph::GetInstance()->AddModel(model);
	return true;
}

void PlayerCharacter::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}