#pragma once

#include "../GameObjects/PlayerCharacter.h"
#include "../GameObjects/Monsters/Monster.h"

//TODO:Finish this

/// <summary>
/// Design: be used for running general game functions
/// like determining when to destroy monsters and the like
/// so put general things in here.
/// 
/// Question: is this bad design?
/// 
/// Goal for now: use to destroy monsters that are at 0 
/// health.
/// </summary>
class GameManager {
public:
	GameManager();
	~GameManager();

	bool OnCreate(std::weak_ptr<PlayerCharacter> player_);


private:
	
	PlayerCharacter* player;
	std::vector<Monster*> monsters;
};