#pragma once
#include "../Component.h"
#include "../SpriteSurface.h"
#include "GUIComponent.h"

class GUIImage : public GUIComponent {
public:
	GUIImage();
	~GUIImage();

	bool OnCreate(std::string name_, glm::vec2 offset_ = glm::vec2(0), 
		glm::vec2 scale_ = glm::vec2(1), float angle_ = 0, glm::vec4 tint_ = glm::vec4(1));

	void Draw(Camera* camera_);

	bool FindContainingPoint();

private:
	SpriteSurface* sprite;
	glm::vec2 offset;

};