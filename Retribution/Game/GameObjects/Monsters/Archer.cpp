#include "Archer.h"
#include "../../../Engine/Rendering/SceneGraph.h"
#include "../../../Engine/Graphics/ShaderHandler.h"
#include "../../../Engine/Rendering/Types/Image.h"
#include "../../../Engine/Math/BoundingBox.h"
#include "../../../Engine/Math/Physics2D.h"

Archer::Archer(glm::vec2 position_) : Monster(position_, 0)
{

}


Archer::~Archer()
{
	//TODO: make sure the projectiles are deleted
	
	//projectiles.clear();
}

bool Archer::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario", true);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());
	
	SetPosition(glm::vec2(40.0f, 40.0f));
	SetScale(glm::vec2(0.1f, 0.1f));
	SetTag("Man");

	return true;
}

void Archer::Update(const float deltaTime_)
{
	Character::Update(deltaTime_);

	
	for (int i = 0; i > projectiles.size(); i++) {
		projectiles[i]->Update(deltaTime_);
	}

}

void Archer::CollisionResponse(std::vector<GameObject*> obj_)
{
}

//I think this is a good first draft here.
void Archer::CreateArrow()
{ 
	std::unique_ptr<Projectile> shot = std::make_unique<Projectile>();
	CollisionHandler::GetInstance()->AddObject(shot.get());
	projectiles.push_back(std::move(shot));
	
}
