#include "CoreEngine.h"
#include "Window.h"
#include "Debug.h"
#include "Scene.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(120), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {

}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit("Debug Log");
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "CoreEngine", __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("BasicShader",
		"Engine/Shaders/SpriteVertShader.glsl",
		"Engine/Shaders/SpriteFragShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("GUIShader",
		"Engine/Shaders/GUIVertShader.glsl",
		"Engine/Shaders/GUIFragShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("GameInterface could not be created", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	timer.Start();

	Debug::Info("Everything was created okay", "CoreEngine.cpp", __LINE__);


	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		timer.UpdateFrameTicks();

		EventListener::Update();

		Update(timer.GetDeltaTime());

		Draw();

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
	glClearColor(0, 0, 0.0f, 1.0f);

	//TODO: should i remove the depth buffer bit? is it redunedt or needed
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->Draw();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
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
