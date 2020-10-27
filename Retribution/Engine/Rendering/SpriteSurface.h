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
	SpriteSurface(bool useView_, GLuint shaderProgram_, std::string name_, glm::vec2 scale_ = glm::vec2(1.0f), float angle_ = 0.0f, glm::vec4 tint_ = glm::vec4(1));
	~SpriteSurface();

	void Draw(Camera* camera_,  glm::vec2 position_);

	float GetWidth() const;
	float GetHeight() const;
	glm::vec2 GetScale() const;
	
	void SetAngle(const float angle_);
	void SetScale(const glm::vec2 scale_);

	void Flip(bool invert_);

private:
	void GenerateBuffers();
	glm::vec2 scale;
	float angle, width, height;
	glm::vec4 tint;
	std::string name;

	std::vector<Vertex2D> vertexList;
	std::vector<Vertex2D> vertexListFlip;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, projLoc, viewLoc, colourLoc;

	GLuint textureID;

	//Use to stop sprite from being effected by view matrix;
	bool useView;;
};
#endif // !SPRITESURFACE_H