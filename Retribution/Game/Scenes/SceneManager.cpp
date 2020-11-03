#include "SceneManager.h"

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
	//TODO: i assume this is what she means by game class

	ShaderHandler::GetInstance()->CreateProgram("BasicShader",
		"Engine/Shaders/SpriteVertShader.glsl",
		"Engine/Shaders/SpriteFragShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("GUIShader",
		"Engine/Shaders/GUIVertShader.glsl",
		"Engine/Shaders/GUIFragShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("ParticleShader",
		"Engine/Shaders/ParticleVertShader.glsl",
		"Engine/Shaders/ParticleFragShader.glsl");

	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
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

void SceneManager::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void SceneManager::Draw()
{
	glClearColor(0, 0, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->Draw();

	SDL_GL_SwapWindow(CoreEngine::GetInstance()->GetWindow()->GetWindow());
}

void SceneManager::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) {

	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		Debug::FatalError("Scene has failed on create", "Game1", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
	
	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
}
