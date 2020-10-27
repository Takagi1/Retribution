#include "SpriteSurface.h"
#include "../Graphics/TextureHandler.h"


SpriteSurface::SpriteSurface(bool useView_, GLuint shaderProgram_, std::string name_, 
	glm::vec2 scale_, float angle_, glm::vec4 tint_)
{
	name = name_;
	angle = angle_;
	tint = glm::vec4(1.0f,0.8f,0.8f, 1.0f);
	shaderProgram = shaderProgram_;
	useView = useView_;

	vertexList.reserve(4);
	vertexList.push_back(Vertex2D());
	vertexList.push_back(Vertex2D());
	vertexList.push_back(Vertex2D());
	vertexList.push_back(Vertex2D());


	vertexList[0].position = glm::vec2(0.0f, 1.0f);
	vertexList[0].texCoord = glm::vec2(0, 0);

	vertexList[1].position = glm::vec2(1.0f, 1.0f);
	vertexList[1].texCoord = glm::vec2(1, 0);

	vertexList[2].position = glm::vec2(0.0f, 0.0f);
	vertexList[2].texCoord = glm::vec2(0, 1);

	vertexList[3].position = glm::vec2(1.0f, 0.0f);
	vertexList[3].texCoord = glm::vec2(1, 1);

	vertexListFlip.reserve(4);
	vertexListFlip.push_back(Vertex2D());
	vertexListFlip.push_back(Vertex2D());
	vertexListFlip.push_back(Vertex2D());
	vertexListFlip.push_back(Vertex2D());


	vertexListFlip[0].position = glm::vec2(1.0f, 1.0f);
	vertexListFlip[0].texCoord = glm::vec2(0, 0);

	vertexListFlip[1].position = glm::vec2(0.0f, 1.0f);
	vertexListFlip[1].texCoord = glm::vec2(1, 0);

	vertexListFlip[2].position = glm::vec2(1.0f, 0.0f);
	vertexListFlip[2].texCoord = glm::vec2(0, 1);

	vertexListFlip[3].position = glm::vec2(0.0f, 0.0f);
	vertexListFlip[3].texCoord = glm::vec2(1, 1);



	if (!TextureHandler::GetInstance()->GetTexture(name)) {
		TextureHandler::GetInstance()->CreateTexture(name_,
			"./Resources/Textures/" + name_);
	}
	textureID = TextureHandler::GetInstance()->GetTextureData(name)->textureID;
	height = TextureHandler::GetInstance()->GetTextureData(name)->height;
	width = TextureHandler::GetInstance()->GetTextureData(name)->width;

	SetScale(scale_);
	GenerateBuffers();
}

SpriteSurface::~SpriteSurface() {
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

float SpriteSurface::GetWidth() const
{
	return width;
}

float SpriteSurface::GetHeight() const
{
	return height;
}

glm::vec2 SpriteSurface::GetScale() const
{
	return scale;
}

void SpriteSurface::SetAngle(const float angle_)
{
	angle = angle_;
}

void SpriteSurface::SetScale(const glm::vec2 scale_)
{
	scale = glm::vec2(scale_.x * width, scale_.y * height);
}

void SpriteSurface::GenerateBuffers()
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

void SpriteSurface::Flip(const bool invert_) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (!invert_) {
		glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexListFlip[0], GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteSurface::Draw(Camera* camera_, glm::vec2 position_)
{

	glUniform1f(textureID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, glm::vec3(position_,0));

	transform = glm::translate(transform, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f)); // move origin of rotation to center of quad
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	transform = glm::translate(transform, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // move origin back
	
	transform = glm::scale(transform, glm::vec3(scale,0));

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