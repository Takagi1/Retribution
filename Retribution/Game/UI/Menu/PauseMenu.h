#ifndef INTERACTIVEMENU_H
#define INTERACTIVEMENU_H

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
#endif // !INTERACTIVEMENU_H
