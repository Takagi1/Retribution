#include "../pch.h"
#include "SceneManager.h"
#include "Scenes/StartScene.h"
#include "Scenes/TestScene.h"



SceneManager::SceneManager() : GameInterface(), currentScene(nullptr), currentSceneNum(0)
{

}


SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = nullptr;
}

bool SceneManager::OnCreate()
{
	if (Engine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		if (!currentScene->OnCreate()) {
			Debug::FatalError("Scene has failed on create", "Game1", __LINE__);
			return false;
		}
		return true;
	}
	Debug::FatalError("Engine scene number is not zero", "Game1.cpp", __LINE__);
	return false;
}

void SceneManager::Input()
{

	currentScene->Input();
}

void SceneManager::Update(const float deltaTime_)
{
	if (currentSceneNum != Engine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void SceneManager::Render(sf::RenderWindow* r_Window)
{
	currentScene->Render(r_Window);
}

void SceneManager::RenderHUD(sf::RenderWindow* r_Window)
{
	currentScene->RenderHUD(r_Window);
}

void SceneManager::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (Engine::GetInstance()->GetCurrentScene()) {

	case 1:
		currentScene = new TestScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		Debug::FatalError("Scene has failed on create", "SceneManager", __LINE__);
		Engine::GetInstance()->Exit();
	}
	currentSceneNum = Engine::GetInstance()->GetCurrentScene();
}