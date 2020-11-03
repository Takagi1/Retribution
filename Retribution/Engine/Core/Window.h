#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "../Graphics/WindowDrawer.h"

class Window
{
public:
	Window();
	~Window();

	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetWidth();
	int GetHeight();
	SDL_Window* GetWindow() const;

private:

	int width, height;
	SDL_Window* window;

};
#endif //WINDOW_H	
