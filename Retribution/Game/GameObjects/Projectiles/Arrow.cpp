#include "Arrow.h"
#include "../../../Engine/Rendering/Types/Image.h"
#include "../../../Game/GameObjects/Character.h"

Arrow::Arrow(Character* parent_, glm::vec2 position_, float depth_) : Projectile(parent_, position_, depth_)
{
}

Arrow::~Arrow()
{
}

bool Arrow::OnCreate(bool isFliped_)
{
	Projectile::OnCreate(isFliped_);
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Arrow.jpg", 0);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

	SetSpeed(100);
	SetScale(glm::vec2(0.05f));
	SetPower(5);
	return true;
}

void Arrow::Update(const float deltaTime_)
{
	Projectile::Update(deltaTime_);
}
