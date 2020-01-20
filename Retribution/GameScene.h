#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Engine.h"
#include "TestCharacter.h"
class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();

	virtual void Input();
	virtual void Update(const float deltaTime_);
	virtual void Render();

	TestCharacter test;

	sf::RectangleShape ground;
};
#endif // !GAMESCENE_H
