#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <string>
#include "SFML/System/Vector2.hpp"

class Window;

class GameInterface {
public:
	GameInterface() {};
	virtual ~GameInterface() {}

	virtual bool OnCreate() = 0;

	virtual void Input(sf::Event inp) = 0 ;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render(Window* window) = 0;
private: 
	sf::Vector2f camera_size;

};

#endif // !GAMEINTERFACE_H