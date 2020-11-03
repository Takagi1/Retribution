#pragma once
#include "../WindowDrawer.h"
#include <glew.h>
#include <SDL_opengl.h>

class OpenGLWindow : public WindowDrawer {
public:
	OpenGLWindow();
	~OpenGLWindow();

	SDL_Window* CreateWindow(std::string name_, int width_, int height_) override;

private:
	void SetPreAttribiutes();
	void SetPostAttributes();

	SDL_GLContext context;
};