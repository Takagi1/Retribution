#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/Engine.h"
#include "../UI/Menu/StartMenu.h"

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	virtual bool OnCreate();

	virtual void Input();
	virtual void Update(const float deltaTime_);
	virtual void Render(sf::RenderWindow* r_Window);
	virtual void RenderHUD(sf::RenderWindow* r_Window);

	StartMenu startMenu;

	sf::Text title;

};
#endif // ! STARTSCENE_H
