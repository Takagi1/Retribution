#include "pch.h"
#include "GameScene.h"
#include "Monster.h"
#include "Hurtbox.h"
#include <stack>


GameScene::GameScene() : counterbox(nullptr)
{
	ground.setSize(sf::Vector2f(2000.0f, 20.0f));
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition(0, 400);
	player = std::make_unique<PlayerCharacter>(this);
	player->body.setPosition(200, 350);
	
	Monster* mon = new Monster(this);
	mon->body.setPosition(100, 350);
	monsters.push_back(mon);

	
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
		
		break;
	case sf::Event::KeyReleased:

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { player->RelRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { player->RelLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { player->RelUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { player->RelDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { player->RelParry(); }
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

	//Counter detection
	if (counterbox) {
		//if body still exists
		if(counterbox->body) {
			std::list<std::unique_ptr<Projectile>>::iterator iter = projectiles.begin();
			for (auto& box : projectiles) {
				if (counterbox->body->getGlobalBounds().intersects(box->box.getGlobalBounds())) {
					counterbox->Trigger(box->power);
					projectiles.erase(iter);
					break;
				}
				iter++;
			}
		}
		counterbox->Update(deltaTime_);
	}
	
	//Monster updates

	for (auto& obj : monsters) {
		if (obj->Collision(ground.getGlobalBounds())) { obj->onGround = true; }
		else { obj->onGround = false; }

		obj->Update(deltaTime_);
	}

	//Projectile updates
	for (auto& obj : projectiles) { obj->Update(deltaTime_); }


	std::list<std::unique_ptr<Projectile>>::iterator iter = projectiles.begin();
	//break fix's the issue however this is a temp solution because of collision with other objects

	//Projectile collision
	for (auto& obj : projectiles) {
		if (player->Collision(obj->box.getGlobalBounds())) {
			player->Damage(iter->get()->power);
			projectiles.erase(iter);
			break;
		}
		iter++;
	}
	
}

void GameScene::Render()
{
	Engine::GetInstance()->GetWindow().draw(player->body);

	Engine::GetInstance()->GetWindow().draw(ground);

	for (auto& obj : monsters) {
		Engine::GetInstance()->GetWindow().draw(obj->body);
	}
	
	for (auto& obj : projectiles) {
		Engine::GetInstance()->GetWindow().draw(obj->box);
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
