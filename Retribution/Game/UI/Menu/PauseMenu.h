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

	void Draw(sf::RenderWindow* r_Window);

private:
	void Exit();

	sf::Text goldDisplay;
};
#endif // !INTERACTIVEMENU_H
