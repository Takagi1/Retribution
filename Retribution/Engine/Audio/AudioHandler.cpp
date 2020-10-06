#include "AudioHandler.h"

std::map<std::string, FMOD::Sound* > AudioHandler::soundPtrList = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channelList = std::map<int, FMOD::Channel*>();

AudioHandler::AudioHandler()
{

}

AudioHandler::~AudioHandler() {

}

AudioHandler * AudioHandler::GetInstance()
{
	if (audioInstance.get() == nullptr) {
		audioInstance.reset(new AudioHandler);
	}
	return audioInstance.get();
}

bool AudioHandler::Initialize(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forward_, glm::vec3 up_)
{
	FMOD::System_Create(&systemPtr);
	
	int driverNum;
	systemPtr->getNumDrivers(&driverNum);
	if (driverNum == 0) {
		Debug::Error("No sound drivers detected", "AudioHandler.cpp", __LINE__);
		return false;
	}

	//TODO: is the amount of channels right?
	systemPtr->init(2, FMOD_INIT_NORMAL, nullptr);
	systemPtr->set3DListenerAttributes(1, &glmToFMOD(position_), &glmToFMOD(velocity_),
		&glmToFMOD(forward_), &glmToFMOD(up_));
	
	return true;
}

void AudioHandler::OnDestroy()
{
	for (auto d : soundPtrList) {
		d.second->release();
		d.second = nullptr;
	}

	for (auto d : channelList) {
		d.second->stop();
		d.second = nullptr;
	}

	systemPtr->release();
	systemPtr = nullptr;
}

void AudioHandler::Update(const float deltaTime_)
{
	systemPtr->update();
}

AudioHandler::~AudioHandler()
{
	OnDestroy();
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 vec_)
{
	FMOD_VECTOR vec;
	vec.x = vec_.x;
	vec.y = vec_.y;
	vec.z = vec_.z;
	return vec;
}

void AudioHandler::LoadSound(const std::string name_, bool loop_, bool is3D_, bool play_)
{
	if (!GetSound(name_)) {
		Debug::Error("Sound already loaded", "AudioHandler", __LINE__);
		return;
	}

	//TODO: Test this extensively because i have no idea if i messed up here with bitwise
	FMOD_MODE mode = FMOD_DEFAULT;
	mode = loop_ | FMOD_LOOP_NORMAL;
	mode = is3D_ | FMOD_3D;
	//TODO: FMOD_SOFTWARE is not found, i have to have it here.
	//Though it may be create stream acording to the paper?
	mode = play_ | FMOD_CREATESTREAM;

	FMOD::Sound* sound_ = nullptr;
	FMOD_CREATESOUNDEXINFO info;

	

	systemPtr->createSound(name_.c_str(), mode, &info, &sound_);


	//TODO: pull the full extend here but im missing the end
	std::string path_ = "./Resources/Audio/" + name_;

	if (sound_) {
		soundPtrList[name_] = sound_;
		Debug::Info("Sound sucssessfully loaded", "AudioHandler", __LINE__);
		return;
	}
	Debug::Error("Sound failed to load", "AudioHandler", __LINE__);
}

FMOD::Sound* AudioHandler::GetSound(std::string name_)
{
	return soundPtrList[name_];
}

int AudioHandler::PlaySound(std::string name_, glm::vec3 position_, glm::vec3 velocity_, float volume_)
{
	int channelID = -1;
	if (GetSound(name_)) {
		LoadSound(name_, false, true, false);
	}
	FMOD::Channel* channel_ = nullptr;

	systemPtr->playSound(GetSound(name_), nullptr, true, &channel_);
	FMOD::Sound* fom = GetSound(name_);

	//if())
	return 0;
}
