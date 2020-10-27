#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) : position(glm::vec2(150,100)), size(100), 
colour(glm::vec4(1.0f, 0.8f, 0.8f, 1.0f))
{
	shaderProgram = shaderProgram_;
	textureID = -1;

	GenerateBuffers();
}

Particle::~Particle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Particle::Update(const float deltaTime_)
{
	lifeTime -= deltaTime_;
}

void Particle::Draw(Camera* camera_)
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	
	//Update the VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &position, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glm::vec4 temp = camera_->GetOrthographic() * camera_->GetView() * glm::vec4(position, 0, 1);
	float attenuation = 1 / sqrtf(0.1f * glm::vec2(temp).length());
	glPointSize(size);

	glUniform1f(sizeLoc, size);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniform4fv(colourLoc, 1, glm::value_ptr(colour));

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	
	glBindVertexArray(0);

	glDisable(GL_PROGRAM_POINT_SIZE);
}

glm::vec2 Particle::GetPosition() const
{
	return position;
}

float Particle::GetLifeTime() const
{
	return lifeTime;
}

void Particle::SetPosition(const glm::vec2 pos_)
{
	position = pos_;
}

void Particle::SetSize(const float size_)
{
	size = size_;
}

void Particle::SetLifeTime(const float lifeTime_)
{
	lifeTime = lifeTime_;
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &position, GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	sizeLoc = glGetUniformLocation(shaderProgram, "size");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
}
