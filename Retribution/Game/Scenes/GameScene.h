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

	void Input(sf::Event inp);
	void Update(const float deltaTime_);
	void Render(Window* window);

	//Enemies
	std::vector<std::shared_ptr<Monster> > monsters;
	
	//Player
	std::unique_ptr<PlayerCharacter> player;

	std::vector<sf::RectangleShape> terrain;

	std::vector<std::shared_ptr<Projectile>> projectiles;

	void Pause();
	void DestroyProjectiles(std::weak_ptr<Projectile> pro);

	void SetGravity(float val);
	float GetGravity();

private:
	bool isPaused;
	float gravity;
};
#endif // !GAMESCENE_H
