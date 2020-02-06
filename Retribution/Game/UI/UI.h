#pragma once

#include "../InteractiveMenu.h"
#include <unordered_map>

class UI
{
public:
	enum Menu {
		PAUSEMENU
	};

	UI();
	~UI();

	static void Init();

	static sf::Font font;

	//HUD
	static sf::Text healthDisplay;
	static sf::Text energyDisplay;
	static sf::Text goldDisplay;

	//Pause Menu
	static sf::RectangleShape pauseWindow;

	//TODO::Finish text box to satesfaction

	static void Scroll(int val_);

	static void CallFunction();

	static void Draw(sf::RenderWindow * r_Window);

private:
	static Menu menu;

	static std::unique_ptr<InteractiveMenu> pauseMenu;

};

