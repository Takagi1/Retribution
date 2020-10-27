// Retribution.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include "Game/Scenes/SceneManager.h"


int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new SceneManager);

	if (!CoreEngine::GetInstance()->OnCreate("Retribution", 800, 600)) {
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}
