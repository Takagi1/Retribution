#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "InteractiveMenu.h"
class PauseMenu :
	public InteractiveMenu
{
public:
	PauseMenu();
	virtual ~PauseMenu();

	virtual void CallFunction();

	void Draw(Window* window);

private:
	void Exit();

	sf::Text goldDisplay;
};
#endif // !PAUSEMENU_H
