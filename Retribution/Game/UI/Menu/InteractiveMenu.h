#pragma once

#include "../MenuObjects/TextBox.h"
#include <vector>

class InteractiveMenu
{
public:
	InteractiveMenu();
	~InteractiveMenu();

	short int counter;

	std::vector<TextBox> textBoxs;

	virtual void Draw(Window * window) = 0;

	void MoveMenu(int val);

	virtual void CallFunction() = 0;

private:


};

