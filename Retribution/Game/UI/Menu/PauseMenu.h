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

private:
	void Exit();
};
#endif // !INTERACTIVEMENU_H
