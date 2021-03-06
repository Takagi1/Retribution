#include "Tile.h"
#include "../../Engine/Math/Physics2D.h"
#include "../../Engine/Rendering/Types/Image.h"
#include "../../Engine/Math/CollisionHandler.h"

Tile::Tile() : GameObject(glm::vec2(0), 0)
{
}

Tile::~Tile()
{
}

bool Tile::OnCreate(glm::vec2 position_)
{
	AddComponent<Physics2D>(this);

	GetComponent<Physics2D>()->SetRigidBody(true);
	GetComponent<Physics2D>()->SetStaticObj(true);

	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Blue.png", 0.0f);

	SetTag("Tile");
	SetPosition(position_);
	SetScale(glm::vec2(10.0f));

	return true;
}

void Tile::Update(const float deltaTime_)
{
}

void Tile::CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_)
{
	GameObject::CollisionResponse(obj_);
}
