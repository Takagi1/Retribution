#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Engine/Core/Engine.h"
#include "PlayerCharacter.h"
#include "Monster.h"
#include "CounterBox.h"
#include "Projectile.h"

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

	//Enemies
	std::vector<std::unique_ptr<Monster> > monsters;

	//Does the counterbox exist
	std::unique_ptr<CounterBox> counterbox;
	
	//Player
	std::unique_ptr<PlayerCharacter> player;

	sf::RectangleShape ground;

	void ClearBox();

	float gravity;

private:

	//HUD
	sf::Text healthDisplay;
	sf::Text energyDisplay;
	sf::Text goldDisplay;

};
#endif // !GAMESCENE_H
