#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics.hpp"
#include <memory>
#include "GameInterface.h"
#include "Scene.h"
#include "Debug.h"

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator =(const Engine&) = delete;
	Engine& operator =(Engine&&) = delete;

	bool OnCreate(std::string name_);
	void Run();
	bool GetIsRunning() const;

	static Engine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	sf::RenderWindow& GetWindow();

	sf::Event input;

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

//DISPLAY SETTINGS

	//Computer display 
	sf::Vector2u display;

	sf::RenderWindow r_Window;


	bool isRunning;

	sf::Clock timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;
};

#endif // !ENGINE_H
