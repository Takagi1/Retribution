#include "../../pch.h"
#include "TestScene.h"


TestScene::TestScene() : GameScene()
{
	//Set Gravity
	gravity = 100;
}


TestScene::~TestScene()
{

}

bool TestScene::OnCreate()
{
	Debug::Info("Creating Test Scene", "TestScene.cpp", __LINE__);
	ground.setSize(sf::Vector2f(2000.0f, 20.0f));
	ground.setFillColor(sf::Color::Blue);
	ground.setPosition(0, 700);

	player = std::make_unique<PlayerCharacter>(this);
	player->body.setPosition(200, 650);

	Debug::Info("Test Scene Completed", "TestScene.cpp", __LINE__);
	return true;
}
