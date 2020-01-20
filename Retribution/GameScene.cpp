#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
	ground.setSize(sf::Vector2f(2000.0f, 20.0f));
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition(0, 400);
	test.body.setPosition(100, 300);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { test.xDir = 1; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { test.xDir = -1; }
	else { test.xDir = 0; }

	//Jump movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && test.onGround) { test.Jump(); }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && test.idle) {
		test.idle = true;

	}
}

void GameScene::Update(const float deltaTime_)
{
	if (test.body.getGlobalBounds().intersects(ground.getGlobalBounds())) { test.onGround = true;  }
	else { test.onGround = false; }

	test.Update(deltaTime_);

}

void GameScene::Render()
{
	Engine::GetInstance()->GetWindow().draw(test.body);
	Engine::GetInstance()->GetWindow().draw(ground);
}