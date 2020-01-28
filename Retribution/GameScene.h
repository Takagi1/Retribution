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

	float gravity;

	//Enemies
	std::vector<std::unique_ptr<Monster> > monsters;
	
	//Player
	std::unique_ptr<PlayerCharacter> player;

	//Does the counterbox exist
	std::unique_ptr<CounterBox> counterbox;

	sf::RectangleShape ground;

	void ClearBox();

	void Pause();
private:

	bool isPaused;

	//HUD
	sf::Text healthDisplay;
	sf::Text energyDisplay;
	sf::Text goldDisplay;

};
#endif // !GAMESCENE_H
