#include "BackgroundSound.h"
#include "../Camera/Camera.h"
#include "AudioHandler.h"

BackgroundSound::BackgroundSound(Camera* camera_)
{
	camera = camera_;
}

BackgroundSound::~BackgroundSound()
{
}

bool BackgroundSound::OnCreate(const std::string name_, bool loop_, bool is3D_, bool stream_)
{
	channelID = -1;
	fileName = name_;

	AudioHandler::GetInstance()->LoadSound(name_, loop_, is3D_, stream_);

	return true;
}

void BackgroundSound::Update(const float deltaTime_)
{
}

void BackgroundSound::PlaySound()
{
	channelID = AudioHandler::GetInstance()->PlaySound(fileName, camera->GetPosition());
}

bool BackgroundSound::IsPlaying()
{
	return AudioHandler::GetInstance()->IsPlaying(channelID);
}
