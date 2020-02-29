#ifndef WINDOW_H
#define WINDOW_H

#include "Options.h"

class Window {

public:
	Window();
	~Window();

	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetWidth();
	int GetHeight();
	sf::RenderWindow* GetWindow() const;

	void SetFrameRateLimit(unsigned int rate);

	void SetView(sf::View* view);

	void ResetView();


	void Clear();
	void Display();

private:
	void SetPreAttribiutes();
	void SetPostAttributes();

	int width, height;
	sf::RenderWindow* window;
	sf::Context context;
	sf::VideoMode video;

	unsigned int fps;

};

#endif WINDOW_H