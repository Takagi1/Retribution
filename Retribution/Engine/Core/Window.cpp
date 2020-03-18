#include "../../pch.h"
#include "Window.h"
#include "Debug.h"

//Resolutions
#define RES_1280X720 1280, 720 
#define RES_1920X1080 1920, 1080

Window::Window() : window(nullptr), height(0), width(0), fps(60)
{

}

Window::~Window()
{

}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	width = width_;
	height = height_;
	
	SetPreAttribiutes();

	video = sf::VideoMode(width, height);

	window = new sf::RenderWindow(video, name_, sf::Style::Default ,context.getSettings());
	if (!window) {
		Debug::FatalError("Window failed to create", "Window.cpp", __LINE__);
		return false;
	}

	//Set FrameRate
	window->setFramerateLimit(60);

	SetPostAttributes();

	return true;
}

void Window::OnDestroy()
{
	delete window;
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

sf::RenderWindow * Window::GetWindow() const
{
	return window;
}

void Window::SetFrameRateLimit(unsigned int rate)
{
	window->setFramerateLimit(rate);
}

void Window::SetView(sf::View* view)
{
	window->setView(*view);
}

void Window::ResetView()
{
	window->setView(window->getDefaultView());
}

void Window::Clear()
{
	window->clear(sf::Color::White);
}

void Window::Display()
{
	window->display();
}


//Set Context here
void Window::SetPreAttribiutes()
{
}

//Spliting these up allow you to lower what you are calling when you need a change
void Window::SetPostAttributes()
{
}
