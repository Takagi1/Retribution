#include "../../pch.h"
#include "GameScene.h"
#include <stack>
#include "../UI/UI.h"


GameScene::GameScene() : gravity(0), isPaused(false)
{
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

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::P) { Pause(); }

		//Manual spawn testing
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::T) {
			std::unique_ptr<Monster> mon = std::make_unique<MonsterTest>(this);
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

		//Monster updates

		for (unsigned int j = 0; j < monsters.size();) {

			//Kill Monster
			if (monsters[j]->GetDead()) {

				player->gold += monsters[j]->GetGold();

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
	}
	else {
		int a = 0;
	}
}

void GameScene::Render(sf::RenderWindow* r_Window)
{
	//Set window view and make it the player position
	Engine::GetInstance()->SetView(player->hurtBox.GetPosition());

	//Draw Game objects
	r_Window->draw(player->hurtBox.Draw());

	for (auto& gro : ground) {
		r_Window->draw(gro);
	}
	

	for (auto& obj : monsters) {
		r_Window->draw(obj->hurtBox.Draw());

		for (auto& proj : obj->proj) {
			r_Window->draw(proj->hurtBox.Draw());
		}
	}
	
	if (player->counterbox) {
		if(player->counterbox->body) r_Window->draw(*player->counterbox->body);
	}
}

void GameScene::RenderHUD(sf::RenderWindow* r_Window)
{
	UI::healthDisplay.setString("Health: " + std::to_string(player->GetHealth()));
	r_Window->draw(UI::healthDisplay);

	UI::energyDisplay.setString("Energy: " + std::to_string(player->GetEnergy()));
	r_Window->draw(UI::energyDisplay);

	UI::goldDisplay.setString("Gold: " + std::to_string(player->gold));
	r_Window->draw(UI::goldDisplay);

	if (isPaused) { 
		r_Window->draw(UI::pauseWindow);
		UI::Draw(r_Window);
	}
}

void GameScene::Pause() { 
	if (isPaused) {
		isPaused = false;
	}
	else {
		isPaused = true;
	}
}
