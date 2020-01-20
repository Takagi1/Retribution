#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
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
	if (Engine::GetInstance()->input.key.code == sf::Keyboard::R) {
		exit(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		test.xDir = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		test.xDir = -1;
	}
	else {
		test.xDir = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		test.yDir = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		test.yDir = -1;
	}
	else {
		test.yDir = 0;
	}
}

void GameScene::Update(const float deltaTime_)
{
	test.Update(deltaTime_);
}

void GameScene::Render()
{
	Engine::GetInstance()->GetWindow().draw(test.body);
}