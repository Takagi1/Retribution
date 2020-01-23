#include "pch.h"
#include "GameScene.h"
#include "Hurtbox.h"
#include <stack>


GameScene::GameScene() : counterbox(nullptr)
{
	ground.setSize(sf::Vector2f(2000.0f, 20.0f));
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition(0,700);
	player = std::make_unique<PlayerCharacter>(this);
	player->body.setPosition(200, 500);
	
	Monster* mon = new Monster(this);
	mon->body.setPosition(100, 500);
	monsters.push_back(mon);

	
}


GameScene::~GameScene()
{
	//TODO: access violation error occurs here when game ends
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);
	return true;
}

void GameScene::Input()
{
	//Direction detection
	//TODO:Can this be improved?
	//TODO:Improve multiple input detection as it is still very bad and unreliable
	switch (Engine::GetInstance()->input.type)
	{
	case sf::Event::KeyPressed:
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { player->PresRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { player->PresLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { player->PresUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { player->PresDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->PresParry(); }

		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::K) { player->PresCounter(); }
		
		break;
	case sf::Event::KeyReleased:

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { player->RelRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { player->RelLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { player->RelUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { player->RelDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->RelParry(); }

		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::K) { player->RelCounter(); }
		break;
	default:
		break;
	}

	//Jump movement
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { test->Jump(); }
}

void GameScene::Update(const float deltaTime_)
{


	//TODO: hit detection finds

	//Player Updates

	if (player->body.getGlobalBounds().intersects(ground.getGlobalBounds())) { player->onGround = true; }
	else { player->onGround = false; }

	player->Update(deltaTime_);
	//Clear projectile when monster die's (how? tests are inconclusive on a good method)

	//std::list<std::unique_ptr<Projectile>>::iterator iter = projectiles.begin();

	if (counterbox) { counterbox->Update(deltaTime_); }
	
	//Monster updates

	for (int j = 0; j < monsters.size();) {
		if (monsters[j]->Collision(ground.getGlobalBounds())) { monsters[j]->onGround = true; }
		else { monsters[j]->onGround = false; }

		monsters[j]->Update(deltaTime_);
		//if(monsters[j])
		//Update projectiles and collision
		for (int i = 0; i < monsters[j]->proj.size();) {

			monsters[j]->proj[i]->Update(deltaTime_);
			if (monsters[j]->IsDead()) {
				//delete monsters[i];
				monsters.erase(monsters.begin() + i);
				monsters.shrink_to_fit();

				//Break if no monsters left
				if (monsters.size() == 0) { return; }

				//else continue on without it
				continue; 
			}
			//Counter detection
			if (counterbox) {
				if (counterbox->body) {
					if (counterbox->body->getGlobalBounds().intersects(monsters[j]->proj[i]->box.getGlobalBounds())) {
						counterbox->Trigger(monsters[j]->proj[i].release());
						monsters[j]->proj.erase(monsters[j]->proj.begin() + i);
 
						continue;
					}
				}
			}
			
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

	/*
	//Projectile updates
	for (auto& obj : projectiles) { obj->Update(deltaTime_); }

	iter = projectiles.begin();
	//break fix's the issue however this is a temp solution because of collision with other objects

	//Projectile collision
	for (auto& obj : projectiles) {
		if (player->Collision(obj->box.getGlobalBounds())) {

			break;
		}
		iter++;
	}
	*/
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
