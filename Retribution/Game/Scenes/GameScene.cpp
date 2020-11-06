#include "GameScene.h"
#include <time.h>
#include <math.h>
#include "../../Engine/Audio/AudioHandler.h"
#include "../../Engine/Parser/XMLParser.h"
#include "../Scripts/MonsterLoader.h"

GameScene::GameScene()
{

}


GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

//TODO: Change variable loads to XML
bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	XMLParser::GetInstance()->ParseFile("Resources/XML/Scenes/GameScene.txt");

	XMLParser::GetInstance()->Enter("Camera");

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(XMLParser::GetInstance()->GetVec3("Location"));

	//CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));


	XMLParser::GetInstance()->Move("PartitionSize");
	CollisionHandler::GetInstance()->OnCreate(XMLParser::GetInstance()->GetFloat("Size"));

	//Create Player

	XMLParser::GetInstance()->Move("Player");
	std::shared_ptr<PlayerCharacter> player = std::make_shared<PlayerCharacter>(XMLParser::GetInstance()->GetVec2("Location"));
	player->OnCreate();

	gameManager.OnCreate(player);
	controller.OnCreate(player);

	SceneGraph::GetInstance()->AddGameObject(std::move(player), "Player");

	XMLParser::GetInstance()->Move("Monsters");

	//emitter = new ParticleEmitter(7, "ParticleShader");
	//emitter->SetPosition(glm::vec2(60));


	//Load Monster's Here

	for (auto m : MonsterLoader::LoadMonsters()) {

		gameManager.AddMonster(m);

		SceneGraph::GetInstance()->AddGameObject(std::move(m));
	}


	//CoreEngine::GetInstance()->GetCamera()->sound = new BackgroundSound(CoreEngine::GetInstance()->GetCamera());

	//CoreEngine::GetInstance()->GetCamera()->sound->OnCreate("LOZ.mp3", false, false, false);

	//CoreEngine::GetInstance()->GetCamera()->sound->PlaySound();

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//Take in player inputs
	controller.Update(deltaTime_);

	SceneGraph::GetInstance()->Update(deltaTime_);

	AudioHandler::GetInstance()->Update(deltaTime_);

	gameManager.Update(deltaTime_);
}

void GameScene::Draw()
{
	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera());

	//emitter->Update(0.03f);
}
