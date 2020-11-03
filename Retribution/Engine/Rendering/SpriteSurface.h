#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <vector>
#include <string>
#include <memory>
#include "../Camera/Camera.h"
#include "../Graphics/ShaderHandler.h"


struct Vertex2D {
	glm::vec2 position;
	glm::vec2 texCoord;
};

class SpriteSurface {
public:
	SpriteSurface(bool useView_, std::string name_, glm::vec2 scale_ = glm::vec2(1.0f), float angle_ = 0.0f);
	~SpriteSurface();

	virtual void Draw(Camera* camera_,  glm::vec2 position_) = 0;

	float GetWidth() const;
	float GetHeight() const;
	glm::vec2 GetScale() const;
	
	void SetAngle(const float angle_);
	void SetScale(const glm::vec2 scale_);

	virtual void Flip(bool invert_) = 0;

protected:
	static std::vector<Vertex2D> vertexList;
	static std::vector<Vertex2D> vertexListFlip;

	glm::vec2 scale;
	float angle, width, height;

	//Use to stop sprite from being effected by view matrix;
	bool useView;

	std::string name;

	unsigned int textureID;

private:



};
#endif // !SPRITESURFACE_H