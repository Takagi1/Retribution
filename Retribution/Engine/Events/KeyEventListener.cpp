#include "KeyEventListener.h"

std::map<SDL_Keycode, bool> KeyEventListener::keys = std::map<SDL_Keycode, bool>();


KeyEventListener::~KeyEventListener()
{
}

void KeyEventListener::PressKey(const SDL_Keycode key_)
{
	keys[key_] = true;
}

void KeyEventListener::ReleaseKey(const SDL_Keycode key_)
{
	keys[key_] = false;
}
