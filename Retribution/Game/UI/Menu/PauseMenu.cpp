#include "../../../pch.h"
#include "PauseMenu.h"
#include "../../../PlayerCharacter.h"
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

	goldDisplay.setFont(UI::font);
	goldDisplay.setPosition(sf::Vector2f(UI::pauseWindow.getGlobalBounds().left + 300 * Options::GetResolution().x / 1920, 1000 * Options::GetResolution().y / 1080));
	goldDisplay.setFillColor(sf::Color::Black);
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

void PauseMenu::Draw(Window * window)
{
	for (auto& all : textBoxs) {
		all.Draw(window);
	}
	goldDisplay.setString("Gold: " + std::to_string(PlayerCharacter::GetGold()));
	window->GetWindow()->draw(goldDisplay);
}

void PauseMenu::Exit()
{
	Engine::GetInstance()->Exit();
}
