#include "Archer.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/BoundingBox.h"

Archer::Archer(glm::vec2 position_) : GameObject(position_, 0)
{

}


Archer::~Archer()
{
}

bool Archer::OnCreate()
{
	AddComponent<Image>();

	GetComponent<Image>()->OnCreate(this);
	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario", true);


	SetPosition(glm::vec2(0.0f, 0.0f));
	SetScale(glm::vec2(100.0f, 100.0f));

	//GetComponent<Physics3D>()->SetMass(1);
	//SceneGraph::GetInstance()->AddModel(model);
	return true;
}

void Archer::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}

void Archer::CreateArrow()
{
}
