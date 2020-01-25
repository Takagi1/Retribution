#include "pch.h"
#include "StartScene.h"
#include "StartScene.h"

StartScene::StartScene() : Scene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	Engine::GetInstance()->SetCurrentScene(1);
	return true;
}

void StartScene::Input()
{
}

void StartScene::Update(const float deltaTime_)
{

}

void StartScene::Render()
{

}

void StartScene::RenderHUD()
{
}
