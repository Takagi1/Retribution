#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <array>
#include <glm/gtx/string_cast.hpp>
#include "../GameObjects/PlayerCharacter.h"
#include "../GUI/HUD.h"
#include "../Scripts/Controller.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Draw();

private:

	PlayerCharacter player;
	HUD hud;

	Controller controller;


};
#endif // !GAMESCENE_H
