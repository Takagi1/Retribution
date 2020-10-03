// Retribution.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include "Game/SceneManager.h"

//TODO: Finish animation and animation controller to a satesfactory degree
//TODO: Improve and finish UI
//TODO: Finish dodge and make a sample animation for it
//TODO: Finish basic monster and create basic ai for it
//TODO: Make basic start screen and loss screen with the option of restarting
//TODO: Create other abilites


/* BUG LIST

if frame rate is unlocked cannot dodge up.

*/

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new SceneManager);

	if (!CoreEngine::GetInstance()->OnCreate("Retribution", 800, 600)) {
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}
