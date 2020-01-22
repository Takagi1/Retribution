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
	test = new TestCharacter(this);
	test->body.setPosition(200, 350);
	
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
		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { test->PresRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { test->PresLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { test->PresUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { test->PresDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { test->PresParry(); }
		
		break;
	case sf::Event::KeyReleased:

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::D) { test->RelRight(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::A) { test->RelLeft(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::W) { test->RelUp(); }
		else if (Engine::GetInstance()->input.key.code == sf::Keyboard::S) { test->RelDown(); }

		if (Engine::GetInstance()->input.key.code == sf::Keyboard::J) { test->RelParry(); }
		break;
	default:
		break;
	}
	
	if (Engine::GetInstance()->input.key.code == sf::Keyboard::R) { exit(0); }

	if (test->idle)
	{

		//Counter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {

			//Direction detection
			//TODO:Can this be improved?
			//TODO:Improve input detection as it is still very bad and unreliable

			//Up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { test->dy = -1; }

			//Right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { test->dx = 1; }

			//Down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { test->dy = 1; }

			//Left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { test->dx = -1; }

			return;
		}


		//Jump movement
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { test->Jump(); }
	}
}

void GameScene::Update(const float deltaTime_)
{
	//TODO: hit detection finds

	//Player Updates

	if (test->body.getGlobalBounds().intersects(ground.getGlobalBounds())) { test->onGround = true; }
	else { test->onGround = false; }

	test->Update(deltaTime_);

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
		if (test->Collision(obj->box.getGlobalBounds())) {
			test->Damage(iter->get()->power);
			projectiles.erase(iter);
			break;
		}
		iter++;
	}
	
}

void GameScene::Render()
{
	Engine::GetInstance()->GetWindow().draw(test->body);

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
	test->idle = true;
}
