#include "pch.h"
#include "GameScene.h"
#include "Hurtbox.h"
#include <stack>


GameScene::GameScene() : counterbox(nullptr), gravity(100)
{
	ground.setSize(sf::Vector2f(2000.0f, 20.0f));
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition(0,700);
	player = std::make_unique<PlayerCharacter>(this);
	player->body.setPosition(200, 500);	
}


GameScene::~GameScene()
{
	
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);
	return true;
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
		
		//Animation test
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::V) { player->animationController.Play("Roll"); }

		//Manual spawn testing
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::T) {
			Monster* mon = new Monster(this);
			mon->body.setPosition(100, 500);
			monsters.push_back(mon);
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
	player->Update(deltaTime_);

	if (counterbox) { counterbox->Update(deltaTime_); }
	
	//Monster updates

	for (int j = 0; j < monsters.size();) {

		//Kill Monster
		if (monsters[j]->IsDead()) {
			delete monsters[j];
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
						monsters[j]->proj.erase(monsters[j]->proj.begin() + i);
						monsters[j]->proj.shrink_to_fit();
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

void GameScene::Render()
{
	Engine::GetInstance()->GetWindow().draw(player->body);

	Engine::GetInstance()->GetWindow().draw(ground);

	for (auto& obj : monsters) {
		Engine::GetInstance()->GetWindow().draw(obj->body);

		for (auto& proj : obj->proj) {
			Engine::GetInstance()->GetWindow().draw(proj->box);
		}
	}

	if (counterbox) {
		if(counterbox->body) Engine::GetInstance()->GetWindow().draw(*counterbox->body);
	}
}

void GameScene::ClearBox()
{
	counterbox.reset();
	player->idle = true;
}
