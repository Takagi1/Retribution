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
	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario", true);


	SetPosition(glm::vec2(0.0f, 0.0f));
	SetDepth(1);
	SetScale(glm::vec2(100.0f,100.0f));

	health = 5;

	//GetComponent<Physics3D>()->SetMass(1);
	//SceneGraph::GetInstance()->AddModel(model);
	return true;
}

void PlayerCharacter::Update(const float deltaTime_)
{
	//TODO:Should i have a check here to see if image is added or would that be redundant 
	//because it should not get here if image is not added?

	//All things gameobject collides with this frame


	GameObject::Update(deltaTime_);

	//null the obj
}

int PlayerCharacter::GetHealth() const
{
	return health;
}

void PlayerCharacter::SetHealth(const int health_)
{
	health = health_;
}
