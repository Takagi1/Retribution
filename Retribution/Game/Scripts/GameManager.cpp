#include "GameManager.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../../Engine/Core/CoreEngine.h"

GameManager::GameManager() : health(0), energy(0) {

}

GameManager::~GameManager() {

}

bool GameManager::OnCreate(std::weak_ptr<PlayerCharacter> player_)
{
    player = player_;
    monsters.reserve(10);

    hud.OnCreate();

    health = player.lock()->GetHealth();
    hud.UpdateHealth(player.lock()->GetHealth());
    energy = player.lock()->GetEnergy();
    hud.UpdateEnergy(player.lock()->GetEnergy());
    return true;
}

void GameManager::Update(const float deltaTime_)
{
    if (player.lock()->GetHealth() <= 0) {
        //TODO: put game over here as player

    }

    //TODO: Camera movement (if player get to far from the center of the screen make it move)
    
    
    //Kill monsters if there health is at 0
    for (size_t i = 0; i < monsters.size();) {
        if (monsters[i].lock()->GetHealth() <= 0) {
            SceneGraph::GetInstance()->RemoveGameObject(monsters[i].lock()->GetName());
            monsters.erase(monsters.begin() + i);
        }
        else { i++; }
    }

    //Update GUI
    if (player.lock()->GetHealth() != health) {
        health = player.lock()->GetHealth();
        hud.UpdateHealth(health);

        if(health <= 0){
            SceneGraph::GetInstance()->Pause();
            printf("GameOver");
        }
    }

    if (player.lock()->GetEnergy() != energy) {
        energy = player.lock()->GetEnergy();
        hud.UpdateEnergy(energy);
    }
}

void GameManager::AddMonster(std::weak_ptr<Monster> monster_)
{
    monsters.push_back(monster_);
}
