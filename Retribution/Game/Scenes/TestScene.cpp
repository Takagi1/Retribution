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
//Remember to reserve the exact amount of ground
bool TestScene::OnCreate()
{
	Debug::Info("Creating Test Scene", "TestScene.cpp", __LINE__);

	view = new sf::View(sf::FloatRect(sf::Vector2f(0, 0), Options::GetResolution()));

	ground.reserve(1);

	sf::RectangleShape piece;
	piece.setSize(sf::Vector2f(2000.0f, 20.0f));
	piece.setFillColor(sf::Color::Blue);
	piece.setPosition(0, 700);
	ground.push_back(piece);

	player = std::make_unique<PlayerCharacter>(this);
	player->hurtBox.SetPosition(200, 650);

	Debug::Info("Test Scene Completed", "TestScene.cpp", __LINE__);
	return true;
}
