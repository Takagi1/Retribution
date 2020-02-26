#pragma once

#include "SFML/Graphics.hpp"

//DISPLAY SETTINGS
struct Display {
public:
	sf::Vector2f resolution;

	sf::Vector2u GetDisplay() {
		return display;
	}
	void SetDisplay(sf::Vector2u display_) {
		display = display_;
	}

private:
	sf::Vector2u display;
};

class Options {
public:
	Options(const Options&) = delete;
	Options(Options&&) = delete;
	Options& operator =(const Options&) = delete;
	Options& operator =(Options&&) = delete;

	Options() = delete;

	static Display display;
};