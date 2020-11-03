#pragma once
#include <string>
#include <SDL.h>
#include "../Core/Debug.h"

enum class DrawType {
	OpenGL
};

class WindowDrawer {
public:
	virtual SDL_Window * CreateWindow(std::string name_, int width_, int height_) = 0;
};