#include "../../pch.h"
#include "StartScene.h"
#include "../UI/UI.h"

StartScene::StartScene() : Scene()
{

}


StartScene::~StartScene()
{

}

bool StartScene::OnCreate()
{
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	
	view = new sf::View(sf::FloatRect(sf::Vector2f(0, 0), Options::GetResolution()));

	title.setString("Retribution");
	title.setFont(UI::font);
	title.setPosition(800, 200);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(60);

	return true;
}

void StartScene::Input()
{
	switch (Engine::GetInstance()->input.type)
	{
	case sf::Event::KeyPressed:
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) {
			startMenu.MoveMenu(-1);
		}
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) {
			startMenu.MoveMenu(1);
		}
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::X) {
			startMenu.CallFunction();
		}
		break;
	default:
		break;
	}
}

//TODO: Find a better way to do this (not the most important thing though)
void StartScene::Update(const float deltaTime_)
{
	startMenu.UpdateTxt();
}

void StartScene::Render(Window* window)
{
	window->Clear();

	startMenu.Draw(window);
	window->GetWindow()->draw(title);

	window->Display();
}
