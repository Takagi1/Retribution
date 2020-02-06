#pragma once

#include "UI/TextBox.h"
#include <vector>

class InteractiveMenu
{
public:
	InteractiveMenu();
	~InteractiveMenu();

	short int counter;

	std::vector<TextBox> textBoxs;

	virtual void Draw(sf::RenderWindow * r_Window);

	void MoveMenu(int val);

	virtual void CallFunction() = 0;

private:


};

