#include "../pch.h"
#include "InteractiveMenu.h"


InteractiveMenu::InteractiveMenu() : counter(0)
{

}


InteractiveMenu::~InteractiveMenu()
{

}

void InteractiveMenu::Draw(sf::RenderWindow * r_Window)
{
	for (auto& all : textBoxs) {
		all.Draw(r_Window);
	}
}

void InteractiveMenu::MoveMenu(int val)
{

	if (counter + val < 0) {
		counter = 0;
		return;
	}
	else if (counter + val == textBoxs.size()) {
		counter = textBoxs.size() - 1;
		return;
	}
	textBoxs[counter].Deselect();
	counter += val;

	textBoxs[counter].Select();
}