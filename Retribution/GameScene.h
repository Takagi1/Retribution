#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Engine.h"
#include "TestCharacter.h"
#include "Monster.h"
#include "CounterBox.h"
#include "Projectile.h"
#include <forward_list>

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();

	virtual void Input();
	virtual void Update(const float deltaTime_);
	virtual void Render();


	//only for enemies
	std::vector<Monster*> monsters;

	//Projectiles
	std::vector<std::unique_ptr<Projectile>> projectiles;

	std::unique_ptr<CounterBox> counterbox;
	
	//player
	TestCharacter* test;

	sf::RectangleShape ground;

	void ClearBox();

};
#endif // !GAMESCENE_H
