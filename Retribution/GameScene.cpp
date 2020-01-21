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
	test = new TestCharacter();
	test->body.setPosition(200, 300);
	
	Monster* mon = new Monster(this);
	mon->body.setPosition(100, 300);
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
	if (Engine::GetInstance()->input.key.code == sf::Keyboard::R) { exit(0); }

	//Horizontal movement

	if (!test->idle) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { test->xDir = 1; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { test->xDir = -1; }
		else { test->xDir = 0; }


		//Jump movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { test->Jump(); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			test->idle = true;
			counterbox = std::make_unique<CounterBox>(this);
		}
	}
}

void GameScene::Update(const float deltaTime_)
{

	//Counter detection
	if (counterbox) {
		//if body still exists
		if(counterbox->body){
			int count = 0;
			for (auto& box : projectiles) {
				if (counterbox->body->getGlobalBounds().intersects(box->box.getGlobalBounds())) {
					projectiles.erase(projectiles.begin() + count);
					break;
				}
				else {
					count += 1;
				}
				
			}
		}
		counterbox->Update(deltaTime_);
	}
	

	//Player Updates

	if (test->body.getGlobalBounds().intersects(ground.getGlobalBounds())) { test->onGround = true; }
	else { test->onGround = false; }

	test->Update(deltaTime_);
	
	//Monster updates

	for (auto& obj : monsters) {
		if (obj->body.getGlobalBounds().intersects(ground.getGlobalBounds())) { obj->onGround = true; }
		else { obj->onGround = false; }

		obj->Update(deltaTime_);
	}

	for (auto& obj : projectiles) {
		int count = 0;
		if (obj->box.getGlobalBounds().intersects(test->body.getGlobalBounds())) {
			test->Damage(obj->power);
			//projectiles.erase(projectiles.begin() + count);

			//projectiles.shrink_to_fit();

		}

		obj->Update(deltaTime_);
		count+= 1;
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
	test->idle = false;
}
