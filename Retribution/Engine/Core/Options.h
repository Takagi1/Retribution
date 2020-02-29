#pragma once

#include "SFML/Graphics.hpp"

//DISPLAY SETTINGS
class Options {
	struct Display {
		friend class Options;
	private:
		sf::Vector2f resolution;
	};


public:
	Options(const Options&) = delete;
	Options(Options&&) = delete;
	Options& operator =(const Options&) = delete;
	Options& operator =(Options&&) = delete;

	Options() = delete;

	static sf::Vector2f GetResolution();
	static void SetResolution(sf::Vector2f res_);

	static void SetDisplayFPS(bool val);
	static bool GetDisplayFPS();

private:
	static Display display;

	static bool fpsDisplay;
};