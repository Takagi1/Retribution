#include "../../../pch.h"
#include "InteractiveMenu.h"


InteractiveMenu::InteractiveMenu() : counter(0)
{

}


InteractiveMenu::~InteractiveMenu()
{

}

void InteractiveMenu::MoveMenu(int val)
{
	if (counter + val < 0 || counter + val == textBoxs.size()) { return; }

	textBoxs[counter].Deselect();
	counter += val;

	textBoxs[counter].Select();
}
