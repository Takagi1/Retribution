#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics.hpp"
#include <memory>
#include "GameInterface.h"
#include "Scene.h"
#include "Debug.h"
#include "Timer.h"
#include "Window.h"


class Engine
{
public:
	sf::Event input;

	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator =(const Engine&) = delete;
	Engine& operator =(Engine&&) = delete;

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning() const;

	static Engine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	//Use to update window from options menu?
	void UpdateWindow();

	void Exit();

private:
	Engine();
	~Engine();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	void OnDestroy();

	void Input();
	void Update(const float deltaTime_);
	void Render();

	Window* window;

	Timer timer;

	//Computer display

	bool isRunning;

	GameInterface* gameInterface;

	int currentSceneNum;
};

#endif // !ENGINE_H
