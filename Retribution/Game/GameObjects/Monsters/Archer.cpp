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

	for (size_t i = 0; i < projectiles.size();) {
		if (projectiles[i].expired()) { projectiles.erase(projectiles.begin() + i);}
		else {
		SceneGraph::GetInstance()->RemoveGameObject(projectiles[i].lock()->GetName());
		i++;
		}

	}
	projectiles.clear();
}

bool Archer::OnCreate()
{
	Character::OnCreate();
	AddComponent<Image>(this);

	int imageLoc = GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Mario.png", 0);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());
	
	SetScale(glm::vec2(0.1f, 0.1f));

	SetMaxHealth(10);
	SetHealth(5);

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

void Archer::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
	GameObject::CollisionResponse(obj_);
}

//I think this is a good first draft here.
void Archer::CreateArrow()
{ 
	//TODO: is this arrow clear bad?
	//Arrow clear
	for (size_t i = 0; i < projectiles.size();) {
		if(projectiles[i].expired()){
			projectiles.erase(projectiles.begin() + i);
		}
		else { i++; }
	}


	std::shared_ptr<Arrow> shot = std::make_shared<Arrow>(this,
		glm::vec2(GetPosition().x + (GetDirFaceing() ? 0.0f : GetBoundingBox().dimentions.x ) , GetPosition().y),
		0);

	shot->OnCreate(GetDirFaceing());
	projectiles.push_back(shot);
	SceneGraph::GetInstance()->AddGameObject(std::move(shot),"Arrow");
}
