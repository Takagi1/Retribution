#include "AudioSource.h"
#include "AudioHandler.h"
#include "../Rendering/GameObject.h"



AudioSource::AudioSource(GameObject* parent_, const std::string name_,
	bool loop_, bool is3D_, bool stream_) : Component()
{
	parent = parent_;
}

AudioSource::~AudioSource()
{
}

bool AudioSource::OnCreate()
{
	return false;
}

void AudioSource::Update(const float deltaTime_)
{
}

void AudioSource::PlaySound()
{
	channelID = AudioHandler::GetInstance()->PlaySound(fileName, glm::vec3(parent->GetPosition(),0));
}

bool AudioSource::IsPlaying()
{
	return AudioHandler::GetInstance()->IsPlaying(channelID);
}
