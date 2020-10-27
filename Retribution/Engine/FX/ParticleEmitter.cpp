#include "ParticleEmitter.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/ShaderHandler.h"
#include "../Math/RandomNumber.h"
#include "../Core/CoreEngine.h"

ParticleEmitter::ParticleEmitter(const int particleAmount_, std::string shaderProgram_, std::string textureName_) : 
	shaderProgram(0), position(glm::vec2(0))
{
	particleAmount = particleAmount_;
	shaderProgram = ShaderHandler::GetInstance()->GetShader(shaderProgram_);

	if (textureName_ != "") {
		if (TextureHandler::GetInstance()->GetTexture(textureName_)) {
			TextureHandler::GetInstance()->CreateTexture(textureName_,
				"./Resources/Textures/" + textureName_);
		}
		textureID = TextureHandler::GetInstance()->GetTextureData(textureName_)->textureID;
	}
	else {
		textureID = -1;
	}

	if (shaderProgram == 0 || textureID == 0) {
		if (shaderProgram == 0) {
			Debug::Error("Shader not found", "ParticleEmitter.cpp", __LINE__);
		}
		if (textureID == 0) {
			Debug::Error("TextureID not found", "ParticleEmitter.cpp", __LINE__);
		}
	}
	else {
		particles.reserve(particleAmount);
		for (int i = 0; i < particleAmount; i++) {
			//TODO: add in the option for texture in Particle but allow for there to not be one.
			//TODO: add in proper access and random values for particles.
			particles.emplace_back(new Particle(shaderProgram));
			particles[i]->SetPosition(position + glm::vec2(RandomNumber::GetRandom(0,100), RandomNumber::GetRandom(0,100)));
			particles[i]->SetSize(3.0f);
			particles[i]->SetLifeTime(0.1f);
		}
	}

	SetDelayUpdate(true);
}

ParticleEmitter::~ParticleEmitter()
{
}

//TODO: note i could move back the draw stuff too draw but for this assignment i need to add it to this.
void ParticleEmitter::Update(const float deltaTime_)
{
	glUseProgram(ShaderHandler::GetInstance()->GetShader("ParticleShader"));
	for (auto part : particles) {
		part->Update(deltaTime_);
		if (part->GetLifeTime() <= 0) {
			part->SetPosition(glm::vec2(RandomNumber::GetRandom(0, 100), RandomNumber::GetRandom(0, 100)));
			part->SetLifeTime(0.1f);
		}
		//TODO: update the particle if it has velocity. optional i think.

		part->Draw(CoreEngine::GetInstance()->GetCamera());
	}
}

void ParticleEmitter::Draw()
{
}

void ParticleEmitter::SetPosition(const glm::vec2 position_)
{
	position = position_;
}

bool ParticleEmitter::FindContainingPoint()
{
	return false;
}
