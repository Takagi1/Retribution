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
	AddComponent<Image>(this);

	SetBoxScale(GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario", true));

	
	SetPosition(glm::vec2(40.0f, 40.0f));
	//SetScale(glm::vec2(50.0f, 50.0f));
	SetTag("Man");

	//GetComponent<Physics3D>()->SetMass(1);
	//SceneGraph::GetInstance()->AddModel(model);
	return true;
}

void Archer::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
}

void Archer::CollisionResponse(std::vector<GameObject*> obj_)
{
}

void Archer::CreateArrow()
{
}
