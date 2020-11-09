#include "Arrow.h"
#include "../../../Engine/Rendering/Types/Image.h"

Arrow::Arrow(GameObject* parent_, glm::vec2 position_, float depth_) : Projectile(parent_, position_, depth_)
{
}

Arrow::~Arrow()
{
}

bool Arrow::OnCreate(bool isFliped_)
{
	Projectile::OnCreate(isFliped_);
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Arrow.jpg", true, 0);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

	SetSpeed(100);
	SetScale(glm::vec2(0.05f));
	return true;
}

void Arrow::Update(const float deltaTime_)
{
	Projectile::Update(deltaTime_);
}
