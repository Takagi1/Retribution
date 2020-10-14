#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../Rendering/Component.h"
#include <string>


class AudioSource : public Component {
public:
	AudioSource(GameObject* parent_);
	~AudioSource();

	bool OnCreate(const std::string name_,
		bool loop_, bool is3D_, bool stream_);
	void Update(const float deltaTime_) override;


	//bool FindContainingPoint() override;

	void PlaySound();
	bool IsPlaying();

private:
	std::string fileName;
	int channelID;

};

#endif // !AUDIOSOURCE_H