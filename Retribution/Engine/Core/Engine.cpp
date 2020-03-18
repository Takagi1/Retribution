#include "../../pch.h"
#include "Engine.h"
#include "../../Game/SceneManager.h"
#include "../../Game/UI/UI.h"
#include "Timer.h"

//DEFINES


std::unique_ptr<Engine> Engine::engineInstance = nullptr;

Engine::Engine() : isRunning(false), gameInterface(nullptr), currentSceneNum(0), fps(60) {

}

Engine::~Engine()
{
	OnDestroy();
}

bool Engine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit("Debug Log");
	Debug::SetSeverity(MessageType::TYPE_INFO);

	
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "CoreEngine", __LINE__);
		return isRunning = false;
	}

	Options::SetResolution(sf::Vector2f(window->GetWidth(), window->GetHeight()));

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("Game Interface was not created", "Engine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	UI::Init();

	//Display fps
	Options::SetDisplayFPS(true);

	timer.Start();

	Debug::Info("Everything was created okay", "Engine.cpp", __LINE__);

	return isRunning = true;
}

void Engine::Run()
{
	while (isRunning) {
		
		timer.UpdateFrameTicks();

		Input();

		Update(timer.GetDeltaTime());

		Render();

		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool Engine::GetIsRunning() const
{
	return isRunning;
}

Engine * Engine::GetInstance()
{
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new Engine);
	}
	return engineInstance.get();
}

void Engine::OnDestroy()
{
	delete gameInterface;
	gameInterface = nullptr;

	exit(0);
}

void Engine::Input()
{
	sf::Event input;
	while (window->GetWindow()->pollEvent(input)) {
		if (gameInterface) {
			gameInterface->Input(input);
		}
	}
}

void Engine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void Engine::Render()
{
	//Render Scene
	if (gameInterface) {
		gameInterface->Render(window);
	}
}

void Engine::SetGameInterface(GameInterface * gameInterface_)
{
	gameInterface = gameInterface_;
}

int Engine::GetCurrentScene()
{
	return currentSceneNum;
}

void Engine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void Engine::Exit()
{
	isRunning = false;
}