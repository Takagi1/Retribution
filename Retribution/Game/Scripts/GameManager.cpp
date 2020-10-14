#include "GameManager.h"

GameManager::GameManager() {

}

GameManager::~GameManager() {

}

bool GameManager::OnCreate(std::weak_ptr<PlayerCharacter> player_)
{
    player = player_;
    return true;
}
