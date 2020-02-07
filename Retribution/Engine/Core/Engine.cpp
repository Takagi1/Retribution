#include "../../pch.h"
#include "Engine.h"
#include "../../Game/SceneManager.h"
#include "../../Game/UI/UI.h"

//DEFINES

//Resolutions
#define RES_1280X720 1280, 720 
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

	view.setSize(RES_1920X1080);
	resolution = view.getSize();

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("Game Interface was not created", "Engine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	UI::Init();

	Debug::Info("Everything was created okay", "Engine.cpp", __LINE__);

	return isRunning = true;
}

void Engine::Run()
{
	while (isRunning) {
		
		sf::Time dt = timer.restart();

		//Debug prevent time breaking things
		if (dt > sf::seconds(0.25)) {
			dt = timer.restart();
		}
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



		if (gameInterface) {
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

	//Render Scene
	if (gameInterface) {
		gameInterface->Render(&r_Window);
	}

	//Reset view
	r_Window.setView(r_Window.getDefaultView());

	//Render HUD
	if (gameInterface) {
		gameInterface->RenderHUD(&r_Window);
	}

	//Display window
	r_Window.display();
	
}

void Engine::SetView(sf::Vector2f pos_)
{
	view.setCenter(pos_);
	r_Window.setView(view);
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