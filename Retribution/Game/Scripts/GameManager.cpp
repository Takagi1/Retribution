#include "GameManager.h"
#include "../../Engine/Rendering/SceneGraph.h"

GameManager::GameManager() {

}

GameManager::~GameManager() {

}

bool GameManager::OnCreate(std::weak_ptr<PlayerCharacter> player_)
{
    player = player_;
    monsters.reserve(10);
    return true;
}

void GameManager::Update(const float deltaTime_)
{
    if (player.lock()->GetHealth() == 0) {
        //TODO: put game over here as player
    }
    
    //Kill monsters if there health is at 0
    for (int i = 0; i > monsters.size();) {
        if (monsters[i].lock()->GetHealth() == 0) {
            SceneGraph::GetInstance()->RemoveGameObject(monsters[i].lock()->GetName());
            monsters.erase(monsters.begin() + i);
        }
        else { i++; }
    }
}

void GameManager::AddMonster(std::weak_ptr<Monster> monster_)
{
    monsters.push_back(monster_);
}
