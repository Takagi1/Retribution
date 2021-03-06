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
	SpriteSurface(bool useView_, std::string name_);
	~SpriteSurface();

	virtual void Draw(Camera* camera_,  glm::mat4 transform_) = 0;

	float GetWidth() const;
	float GetHeight() const;
	glm::vec2 GetScale() const;
	
	virtual void Flip(bool invert_) = 0;

protected:

	glm::vec2 scale;
	float width, height;

	//Use to stop sprite from being effected by view matrix;
	bool useView;

	std::string name;

	unsigned int textureID;

private:



};
#endif // !SPRITESURFACE_H