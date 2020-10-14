#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <array>
#include <glm/gtx/string_cast.hpp>
#include "../Scripts/GameManager.h"
#include "../GUI/HUD.h"
#include "../Scripts/Controller.h"
#include "../GameObjects/Monsters/Archer.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Draw();

private:
	GameManager gameManager;


	//TODO: decide ownership, this is priority 1.
	PlayerCharacter player;
	Archer archer;
	HUD hud;

	Controller controller;


};
#endif // !GAMESCENE_H
