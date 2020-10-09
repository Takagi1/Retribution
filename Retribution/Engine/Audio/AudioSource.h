#pragma once

#include "../Rendering/Component.h"
#include <string>


class AudioSource : public Component {
public:
	AudioSource(GameObject* parent_, const std::string name_, 
		bool loop_, bool is3D_, bool stream_);
	~AudioSource();

	bool OnCreate();
	void Update(const float deltaTime_) override;


	//bool FindContainingPoint() override;

	void PlaySound();
	bool IsPlaying();

private:
	std::string fileName;
	int channelID;

};
