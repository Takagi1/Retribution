#include "Archer.h"
#include "../../../Engine/Rendering/SceneGraph.h"
#include "../../../Engine/Graphics/ShaderHandler.h"
#include "../../../Engine/Rendering/Types/Image.h"
#include "../../../Engine/Math/BoundingBox.h"
#include "../../../Engine/Math/Physics2D.h"
#include "../../GameObjects/Projectiles/Arrow.h"

Archer::Archer(glm::vec2 position_) : Monster(position_, 0), time(2)
{

}


Archer::~Archer()
{
	//TODO: make sure the projectiles are deleted

	for (auto p : projectiles) {
		SceneGraph::GetInstance()->RemoveGameObject(p.lock()->GetName());
	}
}

bool Archer::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	int imageLoc = GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario.png", 0);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());
	
	SetScale(glm::vec2(0.1f, 0.1f));
	SetTag("Man");


	projectiles.reserve(5);
	return true;
}

void Archer::Update(const float deltaTime_)
{
	//Should AI and update be sperate? as in two different functions?

	time -= deltaTime_;
	if (time <= 0) {
		CreateArrow();
		time += 2.0f;
	}

	Character::Update(deltaTime_);
}

void Archer::CollisionResponse(std::weak_ptr<GameObject> obj_)
{
}

//I think this is a good first draft here.
void Archer::CreateArrow()
{ 
	
	std::shared_ptr<Arrow> shot = std::make_shared<Arrow>(this,
		glm::vec2(GetPosition().x + (GetDirFaceing() ? 0.0f : GetBoundingBox().dimentions.x ) , GetPosition().y),
		0);
	shot->OnCreate(GetDirFaceing());
	projectiles.push_back(shot);
	SceneGraph::GetInstance()->AddGameObject(std::move(shot),"Arrow");
}
