#include "../../../pch.h"
#include "PauseMenu.h"
#include "../UI.h"


PauseMenu::PauseMenu()
{
	TextBox textbox;
	textbox.OnCreate(sf::Vector2f(200, 100),
		sf::Vector2f(UI::pauseWindow.getPosition().x + (UI::pauseWindow.getGlobalBounds().width / 2) - 100,
			UI::pauseWindow.getPosition().y + 50));


	textbox.Select();
	textbox.SetText("Options");

	textBoxs.push_back(textbox);

	textbox.OnCreate(sf::Vector2f(200, 100),
		sf::Vector2f(UI::pauseWindow.getPosition().x + (UI::pauseWindow.getGlobalBounds().width / 2) - 100,
			UI::pauseWindow.getPosition().y + 200));

	textbox.Deselect();
	textbox.SetText("Exit");

	textBoxs.push_back(textbox);
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::CallFunction()
{
	if (counter == 0) {

	}
	else if (counter == 1) {
		Exit();
	}
}

void PauseMenu::Exit()
{
	Engine::GetInstance()->Exit();
}
