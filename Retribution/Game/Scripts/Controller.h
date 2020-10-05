#pragma once
#include "../GameObjects/PlayerCharacter.h"



//Used to process player inputs

class Controller {
public:
	Controller();
	~Controller();

	bool OnCreate(PlayerCharacter* player_);

	void Update(const float deltaTime_);

private:
	PlayerCharacter* player;
};