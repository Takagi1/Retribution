#include "OpenGLSpriteSurface.h"

OpenGLSpriteSurface::OpenGLSpriteSurface(bool useView_, GLuint shaderProgram_, std::string name_, 
	glm::vec2 scale_, float angle_, glm::vec4 tint_) : 
	SpriteSurface(useView_, name_, scale_, angle_)
{
	tint = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f);
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

OpenGLSpriteSurface::~OpenGLSpriteSurface()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void OpenGLSpriteSurface::Draw(Camera* camera_, glm::vec2 position_)
{
	glUniform1f(textureID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, glm::vec3(position_, 0));

	transform = glm::translate(transform, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f)); // move origin of rotation to center of quad
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	transform = glm::translate(transform, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // move origin back

	transform = glm::scale(transform, glm::vec3(scale, 0));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));

	if (useView) {
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	}

	glUniform4fv(colourLoc, 1, glm::value_ptr(tint));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLSpriteSurface::Flip(bool invert_)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (!invert_) {
		glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexListFlip[0], GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLSpriteSurface::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	//TEXTURE COORDINATES
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, texCoord));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");

	if (useView) {
		viewLoc = glGetUniformLocation(shaderProgram, "view");
	}
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
}