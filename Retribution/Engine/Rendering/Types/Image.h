#pragma once
#include "../Component.h"
#include "../SpriteSurface.h"
#include "../../Math/BoundingBox.h"

class Image : public Component {
public:
	Image(GameObject* parent_);
	~Image();

	glm::vec2 OnCreate(GLuint shaderID, std::string name_, bool useView_, glm::vec2 offset_ = glm::vec2(0), 
		glm::vec2 scale_ = glm::vec2(1), float angle_ = 0, glm::vec4 tint_ = glm::vec4(1));

	void Update(const float deltaTime_) override;

	void Draw(Camera* camera_) override;

	//Getters
	glm::vec2 GetOffset() const;

	//Setters
	void SetOffset(const glm::vec2 offset_);
	void SetAngle(const float angle_);
	void SetScale(const glm::vec2 scale_);


	bool FindContainingPoint() override;

private:
	SpriteSurface* sprite;
	glm::vec2 offset;

	glm::mat4 transform;

	BoundingBox box;
};