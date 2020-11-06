#include "CoreEngine.h"
#include "Window.h"
#include "Debug.h"
#include "Scene.h"
#include "../Audio/AudioHandler.h"
#include "../Graphics/OpenGL/OpenGLWindow.h"
#include "../Parser/XMLParser.h"
#include <ctime>

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(120), gameInterface(nullptr), currentSceneNum(0), camera(nullptr),
drawer(nullptr), drawType(DrawType::OpenGL) {

}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit("Debug Log");
	Debug::SetSeverity(MessageType::TYPE_INFO);

	CreateDrawer();

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "CoreEngine", __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("GameInterface could not be created", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	AudioHandler::GetInstance()->Initialize();

	timer.Start();

	//Initalize random seed

	
	srand(std::time(0));

	Debug::Info("Everything was created okay", "CoreEngine.cpp", __LINE__);


	return isRunning = true;
}

void CoreEngine::Run()
{
	float time;
	while (isRunning) {
		timer.UpdateFrameTicks();

		EventListener::Update();

		time = timer.GetDeltaTime();
		Update(time);


		Draw();

		timer.FPSCounter(time);

		SDL_Delay(timer.GetSleepTime(fps));	
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

void CoreEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	AudioHandler::GetInstance()->OnDestroy();


	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	delete camera;
	camera = nullptr;

	SDL_Quit();
	exit(0);
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Draw()
{
	if (gameInterface) {
		gameInterface->Draw();
	}


}

void CoreEngine::CreateDrawer()
{
	if (drawType == DrawType::OpenGL) {
		drawer = new OpenGLWindow();
	}
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_, DrawType drawType_)
{
	gameInterface = gameInterface_;
	drawType = drawType_;
}

glm::vec2 CoreEngine::GetWindowSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_)
{

}

void CoreEngine::NotifyOfMouseRelease(glm::vec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_)
{
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera) {
		camera->ProcessMouseScroll(y_);
	}
}

DrawType CoreEngine::GetDrawType() const
{
	return drawType;
}

WindowDrawer* CoreEngine::GetDrawer() const
{
	return drawer;
}

Window* CoreEngine::GetWindow() const
{
	return window;
}
