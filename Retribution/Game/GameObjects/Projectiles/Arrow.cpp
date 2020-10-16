#include "Arrow.h"
#include "../../../Engine/Rendering/Types/Image.h"

Arrow::Arrow(glm::vec2 position_, float depth_) : Projectile(position_, depth_)
{
}

Arrow::~Arrow()
{
}

void Arrow::Update(const float deltaTime_)
{
	Projectile::Update(deltaTime_);
	AddComponent<Image>(this);

	GetComponent<Image>()->OnCreate(ShaderHandler::GetInstance()->GetShader("BasicShader"), "Arrow", true);
	UpdateBoundingBox(GetComponent<Image>()->GetBoundingBox());

}
