#pragma once

#include "Particle.h"
#include "../Rendering/Component.h"

class Camera;

class ParticleEmitter : public Component {
public:
	ParticleEmitter(const int particleAmount_, std::string shaderProgram_, std::string textureName_ = "");
	~ParticleEmitter();

	void Update(const float deltaTime_) override;
	void Draw() override;

	void SetPosition(const glm::vec2 position_);

private:
	int particleAmount;
	GLuint shaderProgram;
	GLuint textureID; //-1 means it does not use a texture, 0 is error

	std::vector<Particle*> particles;

	virtual bool FindContainingPoint();
	glm::vec2 position; //The position of the particle emitter, can be set with the parents pos if needed
};