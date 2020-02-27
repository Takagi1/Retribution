#include "../../pch.h"
#include "GameScene.h"
#include <stack>
#include "../UI/UI.h"
#include "../../SpacialPartition.h"

GameScene::GameScene() : gravity(0), isPaused(false)
{
	projectiles.reserve(15);
} 


GameScene::~GameScene()
{
	
}

void GameScene::Input()
{
	//Direction detection
	switch (Engine::GetInstance()->input.type)
	{
	case sf::Event::KeyPressed:
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { player->PresRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { player->PresLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) {
			if (!isPaused) { player->PresUp(); }
			else { UI::Scroll(-1); }
		}
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) {
			if (!isPaused) { player->PresDown(); }
			else { UI::Scroll(1); }
		}

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->PresParry(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::K) { player->PresCounter(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::L) { player->PresDodge(); }

		if(Engine::GetInstance()->input.key.code == sf::Keyboard::X){	
			if(!isPaused) { 
			// Interact code here
			}
			else { UI::CallFunction(); }
		}

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::G) {  }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::P) { Pause(); }

		//Manual spawn testing
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::T) {
			std::shared_ptr<Monster> mon = std::make_shared<MonsterTest>(this);
			mon->hurtBox.SetPosition(100, 650);
			monsters.push_back(std::move(mon));
		}
		break;
	case sf::Event::KeyReleased:

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { player->RelRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { player->RelLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { player->RelUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { player->RelDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->RelParry(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::K) { player->RelCounter(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::L) { player->RelDodge(); }

		break;
	default:
		break;
	}
}

void GameScene::Update(const float deltaTime_)
{
	if (!isPaused) {
		player->Update(deltaTime_);
		sf::Vector2f display = Options::display.resolution;
		display.x = display.x / 2;
		display.y = display.y / 2;

		//ScreenPartition
		SpacialPartition::GetInstance()->Init(player->hurtBox.GetPosition());

		//Insert Monster
		for (auto& mon : monsters) {
			SpacialPartition::GetInstance()->Insert(display, mon);
		}

		//Insert Projectiles
		for (auto& proj : projectiles) {
			if (proj != nullptr) {
				SpacialPartition::GetInstance()->Insert(display, proj);
			}
		}

		//Insert ground
		for (auto& gro : ground) {
			SpacialPartition::GetInstance()->Insert(display, gro);
		}

		//Update all Monsters (for now but make it so that only monsters on screen get the full thing
		for (unsigned int j = 0; j < monsters.size();) {

			//Kill Monster
			if (monsters[j]->GetDead()) {
				//Safety? 
				monsters[j].reset();

				monsters.erase(monsters.begin() + j);
				monsters.shrink_to_fit();

				//Break if no monsters left
				if (monsters.size() == 0) { return; }

				//else continue on without it
				continue;
			}

			monsters[j]->Update(deltaTime_);

			j++;
		}

		//Projectiles on screen collsion detection
		for (int ptr = 0; ptr < SpacialPartition::GetInstance()->GetProjectiles().size();) {
			if (!SpacialPartition::GetInstance()->GetProjectiles()[ptr].expired()) {
				SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock()->Update(deltaTime_);
				if (SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock()->Collision(player.get())) {
					DestroyProjectiles(SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock());
					continue;
				}
			}
			ptr++;
		}
	}

	UI::Update(deltaTime_);
}

void GameScene::Render(sf::RenderWindow* r_Window)
{
	//Set window view and make it the player position
	Engine::GetInstance()->SetViewPos(player->hurtBox.GetPosition());

	//Draw Game objects
	r_Window->draw(player->hurtBox.Draw());

	for (auto& gro : ground) {
		r_Window->draw(gro);
	}
	
	for (auto& obj : monsters) {
		r_Window->draw(obj->hurtBox.Draw());
	}
	
	for (auto& obj : SpacialPartition::GetInstance()->GetProjectiles()) {
		if (!obj.expired()) {
			r_Window->draw(obj.lock()->hurtBox.Draw());
		}
	}

	if (player->counterbox) {
		if(player->counterbox->body) r_Window->draw(*player->counterbox->body);
	}
}

void GameScene::RenderHUD(sf::RenderWindow* r_Window)
{
	UI::Draw(r_Window);
}

void GameScene::Pause() { 
	if (isPaused) {
		isPaused = false;
	}
	else {
		isPaused = true;
	}
}

void GameScene::DestroyProjectiles(std::weak_ptr<Projectile> pro)
{
	std::vector<std::shared_ptr<Projectile>>::iterator lok = projectiles.begin();
	while (lok != projectiles.end()) {
		if (*lok == pro.lock()) {
			lok->reset();
			projectiles.erase(lok);
			break;
		}
	}
}
