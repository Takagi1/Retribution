#pragma once
#include "../Component.h"
#include "../SpriteSurface.h"
#include "../../Math/BoundingBox.h"

class Image : public Component {
public:
	Image();
	~Image();

	bool OnCreate(GameObject* parent_);
	bool OnCreate(std::string name_, glm::vec2 offset_ = glm::vec2(0), 
		glm::vec2 scale_ = glm::vec2(1), float angle_ = 0, glm::vec4 tint_ = glm::vec4(1));

	void Draw(Camera* camera_);

	//Getters
	glm::vec2 GetOffset() const;
	float GetAngle() const; 
	glm::vec2 GetScale() const;

	//Setters
	void SetOffset(const glm::vec2 offset_);
	void SetAngle(const float angle_);
	void SetScale(const glm::vec2 scale_);


	bool FindContainingPoint();

	void UpdateBox(glm::vec2 pos_);

private:
	SpriteSurface* sprite;
	glm::vec2 offset;

	glm::mat4 transform;

	BoundingBox box;
};