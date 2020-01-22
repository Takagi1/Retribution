#include "pch.h"
#include "Engine.h"
#include "SceneManager.h"

//#include "Scene.h"

//DEFINES

//Resolutions
#define RES_1920X1080 1920, 1080

std::unique_ptr<Engine> Engine::engineInstance = nullptr;

Engine::Engine() : isRunning(false), fps(120), gameInterface(nullptr), currentSceneNum(0) {

}

Engine::~Engine()
{
	OnDestroy();
}

bool Engine::OnCreate(std::string name_)
{
	Debug::DebugInit("Debug Log");
	Debug::SetSeverity(MessageType::TYPE_INFO);

	display = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	//RenderWindow window
	r_Window.create(sf::VideoMode(RES_1920X1080),
		"Retribution",
		sf::Style::Default);

	//Set FrameRate
	r_Window.setFramerateLimit(fps);

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("Game Interface was not created", "Engine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	Debug::Info("Everything was created okay", "Engine.cpp", __LINE__);


	return isRunning = true;
}

void Engine::Run()
{
	while (isRunning) {
		
		sf::Time dt = timer.restart();
		Input();

		Update(dt.asSeconds());

		Render();

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
	while (r_Window.pollEvent(input)) {
		if (input.key.code == sf::Keyboard::Escape)
		{
			isRunning = false;
			break;
		}

		if (gameInterface ) {
			gameInterface->Input();
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
	//Clear window
	r_Window.clear(sf::Color::White);

	if (gameInterface) {
		gameInterface->Render();
	}

	//Display window
	r_Window.display();
}

sf::RenderWindow & Engine::GetWindow()
{
	// TODO: insert return statement here
	return r_Window;
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