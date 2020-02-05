#pragma once
#include "../../InteractiveMenu.h"
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

