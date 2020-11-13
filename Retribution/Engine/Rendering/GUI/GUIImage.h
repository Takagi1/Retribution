#pragma once
#include "GUIComponent.h"
#include "../SpriteSurface.h"
#include "GUIComponent.h"

class GUIImage : public GUIComponent {
public:
	GUIImage(GUIObject* parent_);
	~GUIImage();

	bool OnCreate(std::string name_, glm::vec2 offset_ = glm::vec2(0), 
		glm::vec2 scale_ = glm::vec2(1), float angle_ = 0, glm::vec4 tint_ = glm::vec4(1));

	void Update(const float deltaTime_) override; 

	void Draw(Camera* camera_) override;

	bool FindContainingPoint() override;

	void UpdateTransform(glm::vec2 position_, float angle_, glm::vec2 scale_);
private:
	SpriteSurface* sprite;
	glm::vec2 offset;

	glm::mat4 transform;

};