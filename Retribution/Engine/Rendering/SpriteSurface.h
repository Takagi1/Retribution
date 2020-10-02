#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Camera/Camera.h"
#include "../Graphics/ShaderHandler.h"



struct Vertex2D {
	glm::vec2 position;
	glm::vec2 texCoord;
};

class SpriteSurface {
public:
	SpriteSurface(GLuint shaderProgram_, std::string name_, glm::vec2 scale_ = glm::vec2(1.0f), float angle_ = 0.0f, glm::vec4 tint_ = glm::vec4(1));
	~SpriteSurface();

	void Draw(Camera* camera_,  glm::vec2 position_);

	float GetWidth() const;
	float GetHeight() const;
	
	void SetAngle(const float angle_);
	void SetScale(const glm::vec2 scale_);

private:
	void GenerateBuffers();
	glm::vec2 scale;
	float angle, width, height;
	glm::vec4 tint;
	std::string name;

	std::vector<Vertex2D> vertexList;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, projLoc, colourLoc;

	GLuint textureID;
};
#endif // !SPRITESURFACE_H