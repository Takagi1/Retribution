#ifndef IMAGE_H
#define IMAGE_H

#include "../Component.h"
#include "../SpriteSurface.h"
#include "../../Math/BoundingBox.h"

enum class DrawType;

class Image : public Component {
public:
	Image(GameObject* parent_);
	~Image();

	bool OnCreate(GLuint shaderID, std::string name_, float depth_, glm::vec2 offset_ = glm::vec2(0), 
		glm::vec2 scale_ = glm::vec2(1), float angle_ = 0, glm::vec4 tint_ = glm::vec4(1));

	void Update(const float deltaTime_) override;

	void Draw() override;

	//Getters
	glm::vec2 GetOffset() const;

	//Setters
	void SetOffset(const glm::vec2 offset_);
	void UpdateTransform(glm::vec2 position_, float angle_, glm::vec2 scale_);


	bool FindContainingPoint() override;

	BoundingBox GetBoundingBox() const;

	void Flip(bool invert_);

	void SetImageLoc(int loc_);
	int GetImageLoc() const;

private:

	SpriteSurface* sprite;
	glm::vec2 offset;

	glm::mat4 transform;

	int imageLoc;

	BoundingBox box;

	bool flip;

	float depth;

	DrawType type;

};
#endif // !IMAGE_H