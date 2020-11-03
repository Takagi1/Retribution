#include "GameScene.h"
#include <time.h>
#include <math.h>
#include "../../Engine/Audio/AudioHandler.h"

GameScene::GameScene()
{

}


GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}


bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate(10000.0f);

	//Create Player

	std::shared_ptr<PlayerCharacter> player = std::make_shared<PlayerCharacter>(glm::vec2(450,0));
	player->OnCreate();

	gameManager.OnCreate(player);
	controller.OnCreate(player);

	SceneGraph::GetInstance()->AddGameObject(std::move(player), "Player");



	//emitter = new ParticleEmitter(7, "ParticleShader");
	//emitter->SetPosition(glm::vec2(60));

	
	std::shared_ptr<Archer> archer = std::make_shared<Archer>(glm::vec2(80,0));

	archer->OnCreate();
	gameManager.AddMonster(archer);

	SceneGraph::GetInstance()->AddGameObject(std::move(archer), "Archer");


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
