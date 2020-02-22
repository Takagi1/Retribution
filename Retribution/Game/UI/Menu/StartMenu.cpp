#include "../../../pch.h"
#include "StartMenu.h"
#include "../UI.h"


StartMenu::StartMenu()
{
	float x = Options::display.resolution.x / 1920;
	float y = Options::display.resolution.y / 1080;

	TextBox textbox;
	textbox.OnCreate(sf::Vector2f(200, 100), sf::Vector2f(880 * x, 320 * y));

	textbox.Select();
	textbox.SetText("New Game");
	
	textBoxs.push_back(textbox);

	textbox.OnCreate(sf::Vector2f(200, 100), sf::Vector2f(880 * x, 500 * y));

	textbox.Deselect();
	textbox.SetText("Exit");

	textBoxs.push_back(textbox);
}


StartMenu::~StartMenu()
{
}

void StartMenu::CallFunction()
{
	if (counter == 0) {
		Start();
	}
	else if (counter == 1) {
		Exit();
	}
}

void StartMenu::UpdateTxt()
{
	textBoxs[0].SetText("New Game");
	textBoxs[1].SetText("Exit");
}

void StartMenu::Start()
{
	Engine::GetInstance()->SetCurrentScene(1);
}

void StartMenu::Exit()
{
	Engine::GetInstance()->Exit();
}
