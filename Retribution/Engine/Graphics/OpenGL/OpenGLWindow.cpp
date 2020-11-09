#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow() : WindowDrawer(), context(nullptr)
{

}

OpenGLWindow::~OpenGLWindow()
{
	SDL_GL_DeleteContext(context);
}

SDL_Window* OpenGLWindow::CreateWindow(std::string name_, int width_, int height_)
{
	SetPreAttribiutes();

	SDL_Window* window;
	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width_, height_,
		SDL_WINDOW_OPENGL);

	if (!window) {
		Debug::FatalError("Window failed to create", "OpenGLDrawer.cpp", __LINE__);
		return nullptr;
	}

	context = SDL_GL_CreateContext(window);

	SetPostAttributes();

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::FatalError("GLEW failed to initialize", "Window.cpp", __LINE__);

		return nullptr;
	}

	//TODO: test altering the objects with depth and then using depth test for the depth system

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width_, height_);

	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	return window;
}

void OpenGLWindow::SetPreAttribiutes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

void OpenGLWindow::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
