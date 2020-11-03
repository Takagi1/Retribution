#include "Window.h"
#include "Debug.h"
#include "CoreEngine.h"

Window::Window() :window(nullptr), width(0), height(0)
{


}


Window::~Window()
{
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("SDL failed to initalize", "Window.cpp", __LINE__);
		return false;
	}

	width = width_;
	height = height_;


	window = CoreEngine::GetInstance()->GetDrawer()->CreateWindow(name_, width_, height_);

	if (window == nullptr) { return false; }

	return true;
}

void Window::OnDestroy()
{
	//SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

