#ifndef UI_H
#define UI_H

#include "Menu/InteractiveMenu.h"
#include <unordered_map>

class UI
{
public:
	static void Init();

	static sf::Font font;

	static sf::Text fpsCounter;

	//Pause Menu
	static sf::RectangleShape pauseWindow;

	static void Update(const float deltaTime_);

	static void Scroll(int val_);

	static void CallFunction();

	static void Draw(Window * window);

	static void Pause();
private:

	UI();
	~UI();
	enum Menu {
		DEFAULT,
		PAUSEMENU
	};

	static Menu menu;

	static std::unique_ptr<InteractiveMenu> pauseMenu;

	//HUD
	static sf::Text healthDisplay;
	static sf::Text energyDisplay;
};

#endif // !UI_H