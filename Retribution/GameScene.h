#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Engine.h"
#include "PlayerCharacter.h"
#include "Monster.h"
#include "CounterBox.h"
#include "Projectile.h"
#include <list>

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
	//std::list<std::unique_ptr<Projectile>> projectiles;

	std::unique_ptr<CounterBox> counterbox;
	
	//player
	std::unique_ptr<PlayerCharacter> player;

	sf::RectangleShape ground;

	void ClearBox();


	float gravity;

private:



};
#endif // !GAMESCENE_H
