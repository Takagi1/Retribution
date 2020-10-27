#include "AudioSource.h"
#include "AudioHandler.h"
#include "../Rendering/GameObject.h"



AudioSource::AudioSource(GameObject* parent_) : Component()
{
	parent = parent_;
}

AudioSource::~AudioSource()
{

}

bool AudioSource::OnCreate(const std::string name_,
	bool loop_, bool is3D_, bool stream_)
{
	channelID = -1;
	fileName = name_;

	AudioHandler::GetInstance()->LoadSound(name_, loop_, is3D_, stream_);

	return true;
}

void AudioSource::Update(const float deltaTime_)
{
	AudioHandler::GetInstance()->UpdateChannelPositionVelocity(channelID, glm::vec3(parent->GetPosition(),0));
}

void AudioSource::PlaySound()
{
	channelID = AudioHandler::GetInstance()->PlaySound(fileName, glm::vec3(parent->GetPosition(),0));
}

bool AudioSource::IsPlaying()
{
	return AudioHandler::GetInstance()->IsPlaying(channelID);
}

void AudioSource::Draw()
{
}

bool AudioSource::FindContainingPoint()
{
	return false;
}
