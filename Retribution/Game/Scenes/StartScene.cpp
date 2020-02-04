#include "../../pch.h"
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
	
	return true;
}

void StartScene::Input()
{
	switch (Engine::GetInstance()->input.type)
	{
	case sf::Event::KeyPressed:
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::Z) {
			Engine::GetInstance()->SetCurrentScene(1);
		}
	default:
		break;
	}
}

void StartScene::Update(const float deltaTime_)
{

}

void StartScene::Render(sf::RenderWindow* r_Window)
{

}

void StartScene::RenderHUD(sf::RenderWindow* r_Window)
{
}
