#ifndef KEYEVENTLISTENER_H
#define KEYEVENTLISTENER_H

#include <SDL.h>
#include <map>

class KeyEventListener {
public:
	KeyEventListener(const KeyEventListener&) = delete;
	KeyEventListener(KeyEventListener&&) = delete;
	KeyEventListener& operator =(const KeyEventListener&) = delete;
	KeyEventListener& operator =(KeyEventListener&&) = delete;

	KeyEventListener() = delete;
	~KeyEventListener();

	static void PressKey(const SDL_Keycode key_);

	static void ReleaseKey(const SDL_Keycode key_);

	static std::map<SDL_Keycode, bool> keys;
};
#endif // !KEYEVENTLISTENER_H