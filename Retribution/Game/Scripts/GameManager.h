#pragma once

#include "../GameObjects/PlayerCharacter.h"
#include "../GameObjects/Monsters/Monster.h"
#include "../GUI/HUD.h"

//TODO:Finish this

/// <summary>
/// Design: be used for running general game functions
/// like determining when to destroy monsters and the like
/// so put general things in here.
/// 
/// 
/// Goal for now: use to destroy monsters that are at 0 
/// health.
/// </summary>
class GameManager {
public:
	GameManager();
	~GameManager();

	bool OnCreate(std::weak_ptr<PlayerCharacter> player_);
	void Update(const float deltaTime_);
	void AddMonster(std::weak_ptr<Monster> monster_);

private:
	
	std::weak_ptr<PlayerCharacter> player;
	std::vector<std::weak_ptr<Monster>> monsters;


	HUD hud;

	int health;
	int energy;
};