#include "Options.h"

Options::Display Options::display = Display();
bool Options::fpsDisplay = false;

sf::Vector2f Options::GetResolution()
{
	return display.resolution;
}

void Options::SetResolution(sf::Vector2f res_)
{
	display.resolution = res_;
}

void Options::SetDisplayFPS(bool val)
{
	fpsDisplay = val;
}

bool Options::GetDisplayFPS()
{
	return fpsDisplay;
}
