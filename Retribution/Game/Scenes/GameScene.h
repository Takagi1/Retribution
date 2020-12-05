#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <array>
#include <glm/gtx/string_cast.hpp>
#include "../Scripts/GameManager.h"
#include "../Scripts/Controller.h"
#include "../GameObjects/Monsters/Archer.h"
#include "../../Engine/FX/ParticleEmitter.h"


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

	Controller controller;

};
#endif // !GAMESCENE_H
