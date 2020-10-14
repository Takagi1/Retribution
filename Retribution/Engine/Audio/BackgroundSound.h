#pragma once
#include <string>
class Camera;


class BackgroundSound {
public: 
	BackgroundSound(Camera* camera_);
	~BackgroundSound();

	bool OnCreate(const std::string name_,
		bool loop_, bool is3D_, bool stream_);
	void Update(const float deltaTime_);

	void PlaySound();
	bool IsPlaying();

private:
	std::string fileName;
	int channelID;

	Camera* camera;
};