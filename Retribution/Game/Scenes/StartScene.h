#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/Engine.h"
#include "../UI/MenuObjects/TextBox.h"
#include <array>

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	virtual bool OnCreate();

	virtual void Input(sf::Event inp);
	virtual void Update(const float deltaTime_);
	virtual void Render(Window* window);

	//StartMenu startMenu;

private:
	sf::Text title;

	std::array<TextBox, 2> textBoxs;

	void MoveMenu(int val);
	void CallFunction();
	int counter;


};
#endif // ! STARTSCENE_H
