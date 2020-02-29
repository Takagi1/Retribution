#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "../Engine/Core/Engine.h"
#include "UI/UI.h"


class SceneManager : public GameInterface
{
public:
	SceneManager();
	virtual ~SceneManager();
	virtual bool OnCreate() override;

	virtual void Input();
	virtual void Update(const float deltaTime_) override;
	virtual void Render(Window* window) override;

private:
	Scene* currentScene;
	int currentSceneNum;
	void BuildScene();
};
#endif // !SCENEMANAGER_H