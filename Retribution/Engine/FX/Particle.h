#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Camera/Camera.h"


//Responsible for rendering the particle

//TODO: Curently there is no option to pass a texture to the particle but that is something that is optional that may
//give options in the future


//TODO: Add in CPU Acceleration
class Particle {
public:
	Particle(GLuint shaderProgram_, GLuint textureID_ = 0);
	~Particle();

	void Update(const float deltaTime_);
	void Draw(Camera* camera_);

	//Getters

	glm::vec2 GetPosition() const;
	float GetLifeTime() const;

	//Setters

	void SetPosition(const glm::vec2 pos_);
	void SetSize(const float size_);
	void SetLifeTime(const float lifeTime_);

private:
	void GenerateBuffers();

	GLuint VAO, VBO, shaderProgram;

	GLuint sizeLoc, viewLoc, projLoc, colourLoc;

	GLuint textureID;

	glm::vec2 position;
	glm::vec2 velocity;
	float lifeTime;
	glm::vec4 colour;
	float size;

};

#endif // !PARTICLE_H