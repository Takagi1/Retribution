#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class Window;

class GameInterface {
public:

	GameInterface() {}
	virtual ~GameInterface() {}

	virtual bool OnCreate() = 0;

	virtual void Input() = 0 ;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render(Window* window) = 0;

private:
	sf::Vector2f camera_size;

};

#endif // !GAMEINTERFACE_H