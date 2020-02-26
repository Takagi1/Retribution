#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/Engine.h"
#include "../../PlayerCharacter.h"
#include "../Monsters/MonsterTest.h"
#include "../../Projectile.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate() = 0;

	void Input();
	void Update(const float deltaTime_);
	void Render(sf::RenderWindow* r_Window);
	void RenderHUD(sf::RenderWindow* r_Window);

	float gravity;

	//Enemies
	std::vector<std::shared_ptr<Monster> > monsters;
	
	//Player
	std::unique_ptr<PlayerCharacter> player;

	std::vector<sf::RectangleShape> ground;

	std::vector<std::shared_ptr<Projectile>> projectiles;

	//PAUSE MENU 

	void Pause();

	void DestroyProjectiles(std::weak_ptr<Projectile> pro);

private:
	bool isPaused;
};
#endif // !GAMESCENE_H
