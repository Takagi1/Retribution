#pragma once

#include "SFML/Graphics.hpp"

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
	static Display display;
};