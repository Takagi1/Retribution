// Retribution.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include "SceneManager.h"

//TODO: Finish animation and animation controller to a satesfactory degree
//TODO: Improve UI
//TODO: Finish dodge and make a sample animation for it
//TODO: Finish basic monster and create basic ai for it
//TODO: Make basic start screen and loss screen with the option of restarting
//TODO: Make GameScene into a virtual so that all GameScenes inherit the basic input, update, render functions

int main(int argc, char* argv[]) {
	Engine::GetInstance()->SetGameInterface(new SceneManager);

	if (!Engine::GetInstance()->OnCreate("GAME258_Engine")) {
		return 0;
	}

	Engine::GetInstance()->Run();

	return 0;
}
