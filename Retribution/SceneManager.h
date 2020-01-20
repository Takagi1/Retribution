#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Engine.h"
#include "StartScene.h"
#include "GameScene.h"


class SceneManager : public GameInterface
{
public:
	SceneManager();
	virtual ~SceneManager();
	virtual bool OnCreate() override;

	virtual void Input();
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;

private:
	Scene* currentScene;
	int currentSceneNum;
	void BuildScene();
};
#endif // !SCENEMANAGER_H