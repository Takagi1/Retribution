#include "pch.h"
#include "GameScene.h"
#include "Hurtbox.h"
#include <stack>


GameScene::GameScene() : counterbox(nullptr), gravity(0), isPaused(false)
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

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { player->PresUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { player->PresDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->PresParry(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::K) { player->PresCounter(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::L) { player->PresDodge(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::P) { Pause(); }

		//Manual spawn testing
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::T) {
			std::unique_ptr<Monster> mon = std::make_unique<Monster>(this);
			mon->body.setPosition(100, 500);
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

		if (counterbox) { counterbox->Update(deltaTime_); }

		//Monster updates

		for (int j = 0; j < monsters.size();) {

			//Kill Monster
			if (monsters[j]->IsDead()) {

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

			//Update projectiles and collision
			for (int i = 0; i < monsters[j]->proj.size();) {

				monsters[j]->proj[i]->Update(deltaTime_);

				//Counter/Parry detection
				if (counterbox) {
					if (counterbox->body) {
						if (counterbox->body->getGlobalBounds().intersects(monsters[j]->proj[i]->box.getGlobalBounds())) {

							counterbox->Trigger(std::move(monsters[j]->proj[i]));
							//if not reduced blocked
							if (counterbox->GetType() != 2 && !counterbox->hangTime) {
								monsters[j]->proj.erase(monsters[j]->proj.begin() + i);
								monsters[j]->proj.shrink_to_fit();
							}
							continue;
						}
					}
				}

				//Get hit by projectiles
				if (player->Collision(monsters[j]->proj[i]->box.getGlobalBounds())) {
					player->Damage(monsters[j]->proj[i]->power);
					monsters[j]->proj.erase(monsters[j]->proj.begin() + i);
					monsters[j]->proj.shrink_to_fit();
				}
				else {
					i++;
				}
			}
			j++;
		}
	}
}

void GameScene::Render(sf::RenderWindow* r_Window)
{
	//Set window view and make it the player position
	Engine::GetInstance()->SetView(player->body.getPosition());

	//Draw Game objects
	r_Window->draw(player->body);

	r_Window->draw(ground);

	for (auto& obj : monsters) {
		r_Window->draw(obj->body);

		for (auto& proj : obj->proj) {
			r_Window->draw(proj->box);
		}
	}
	
	if (counterbox) {
		if(counterbox->body) r_Window->draw(*counterbox->body);
	}
}

void GameScene::RenderHUD(sf::RenderWindow* r_Window)
{
	UI::healthDisplay.setString("Health: " + std::to_string(player->health));
	r_Window->draw(UI::healthDisplay);

	UI::energyDisplay.setString("Energy: " + std::to_string(player->GetEnergy()));
	r_Window->draw(UI::energyDisplay);

	UI::goldDisplay.setString("Gold: " + std::to_string(player->gold));
	r_Window->draw(UI::goldDisplay);

	if (isPaused) { 
		r_Window->draw(UI::pauseWindow);
		r_Window->draw(UI::optionBox.GetText());
		r_Window->draw(UI::exitBox.GetText());
	}
}

void GameScene::ClearBox()
{
	counterbox.reset();
	player->animationState["Idle"] = true;
}

void GameScene::Pause() { 
	if (isPaused) {
		isPaused = false;
	}
	else {
		isPaused = true;
	}
}
