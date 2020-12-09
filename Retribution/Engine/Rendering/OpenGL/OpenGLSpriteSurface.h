#pragma once
#include "../SpriteSurface.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>


class OpenGLSpriteSurface : public SpriteSurface {
public:
	OpenGLSpriteSurface(bool useView_, GLuint shaderProgram_, std::string name_, glm::vec4 tint_ = glm::vec4(1));
	~OpenGLSpriteSurface();

	void Draw(Camera* camera_, glm::mat4 transform_) override;

	void Flip(bool invert_) override;

private:
	void GenerateBuffers();

	GLuint shaderProgram;

	GLuint VAO, VBO;

	GLuint modelLoc, projLoc, viewLoc, colourLoc;

	glm::vec4 tint;

	static std::vector<Vertex2D> vertexList;
	static std::vector<Vertex2D> vertexListFlip;

};