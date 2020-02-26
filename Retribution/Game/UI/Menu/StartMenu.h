#ifndef STARTMENU_H
#define STARTMENU_H

#include "InteractiveMenu.h"
class StartMenu :
	public InteractiveMenu
{
public:
	StartMenu();
	virtual ~StartMenu();

	virtual void CallFunction();

	void UpdateTxt();

private:
	void Start();
	void Exit();
};

#endif // !STARTMENU_H