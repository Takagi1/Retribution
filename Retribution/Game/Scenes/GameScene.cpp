#include "../../pch.h"
#include "GameScene.h"
#include <stack>
#include "../UI/UI.h"
#include "../../SpacialPartition.h"

GameScene::GameScene() : gravity(0), isPaused(false)
{
	view = new sf::View();

	projectiles.reserve(15);
} 


GameScene::~GameScene()
{
	
}

void GameScene::Input(sf::Event input)
{
	//Direction detection
	switch (input.type)
	{
	case sf::Event::KeyPressed:

		switch (input.key.code)
		{
		case sf::Keyboard::D:
			player->PresRight();
			break;

		case sf::Keyboard::A:
			player->PresLeft();
			break;

		case sf::Keyboard::W:
			if (!isPaused) { player->PresUp(); }
			else { UI::Scroll(-1); }
			break;

		case sf::Keyboard::S:
			if (!isPaused) { player->PresDown(); }
			else { UI::Scroll(1); }
			break;

		case sf::Keyboard::J:
			player->PresParry();
			break;

		case sf::Keyboard::K:
			player->PresCounter();
			break;

		case sf::Keyboard::L:
			player->PresDodge();
			break;

		case sf::Keyboard::LShift:
			player->PresAlt();
			break;

		case sf::Keyboard::X:
			if (!isPaused) {
				// Interact code here
			}
			else { UI::CallFunction(); }
			break;

		case sf::Keyboard::P:
			Pause();
			break;

		default:
			break;
		}

		//Manual spawn testing
		if (input.key.code == sf::Keyboard::T) {
			std::shared_ptr<Monster> mon = std::make_shared<MonsterTest>(this);
			mon->hurtBox.SetPosition(100, 650);
			monsters.push_back(std::move(mon));
		}
		break;

	case sf::Event::KeyReleased:

		switch (input.key.code)
		{
		case sf::Keyboard::D:
			player->RelRight();
			break;

		case sf::Keyboard::A:
			player->RelLeft();
			break;

		case sf::Keyboard::W:
			player->RelUp();
			break;

		case sf::Keyboard::S:
			player->RelDown();
			break;

		case sf::Keyboard::J:
			player->RelParry();
			break;

		case sf::Keyboard::K:
			player->RelCounter();
			break;

		case sf::Keyboard::LShift:
			player->RelAlt();
			break;

		default:
			break;
		}

		break;

	default:
		break;
	}
}

void GameScene::Update(const float deltaTime_)
{
	if (!isPaused) {

		//Update Player
		player->Update(deltaTime_);

		//TODO: remove this from the update (if its a good idea)
		//Get sceen display
		sf::Vector2f display = Options::GetResolution();
		display.x = display.x / 2;
		display.y = display.y / 2;

		//ScreenPartition
		SpacialPartition::GetInstance()->Init(player->hurtBox.GetPosition());

		//Insert Monster
		for (auto& mon : monsters) {
			SpacialPartition::GetInstance()->Insert(display, mon);
		}

		//Insert ground
		for (auto& gro : terrain) {
			SpacialPartition::GetInstance()->Insert(display, gro);
		}

		//Update all Monsters (for now but intent is to make it so that only monsters on screen get the full thing
		for (unsigned int i = 0; i < monsters.size();) {

			//Kill Monster
			if (monsters[i]->GetDead()) {

				//Safety? 
				monsters[i].reset();

				monsters.erase(monsters.begin() + i);
				monsters.shrink_to_fit();

				//Break if no monsters left
				if (monsters.size() == 0) { return; }

				//else continue on without it
				continue;
			}

			monsters[i]->Update(deltaTime_);

			i++;
		}

		//Insert Projectiles
		//Is here so that any projectiles that are destroyed because of monster death do not get added to the partition saving time
		for (auto& proj : projectiles) {
			if (proj != nullptr) {
				SpacialPartition::GetInstance()->Insert(display, proj);
			}
		}

		//Projectiles on screen collsion detection
		for (int ptr = 0; ptr < SpacialPartition::GetInstance()->GetProjectiles().size();) {
			if (!SpacialPartition::GetInstance()->GetProjectiles()[ptr].expired()) {
				SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock()->Update(deltaTime_);
				if (SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock()->Collision(player.get())) {
					DestroyProjectiles(SpacialPartition::GetInstance()->GetProjectiles()[ptr].lock());
					continue;
				}
			}
			ptr++;
		}
	}

	UI::Update(deltaTime_);
}

void GameScene::Render(Window* window)
{
	window->Clear();

	//Set window view and make it the player position
	view->setCenter(player->hurtBox.GetPosition());

	window->SetView(view);

	//Draw Game objects
	window->GetWindow()->draw(player->hurtBox.Draw());

	for (auto& gro : terrain) {
		window->GetWindow()->draw(gro);
	}
	
	for (auto& obj : monsters) {
		window->GetWindow()->draw(obj->hurtBox.Draw());
	}
	
	for (auto& obj : SpacialPartition::GetInstance()->GetProjectiles()) {
		if (!obj.expired()) {
			window->GetWindow()->draw(obj.lock()->hurtBox.Draw());
		}
	}

	if (player->counterbox) {
		if(player->counterbox->body) window->GetWindow()->draw(*player->counterbox->body);
	}

//Render HUD

	window->ResetView();

	UI::Draw(window);

	//Display window
	window->Display();
}

void GameScene::Pause() { 
	if (isPaused) {
		isPaused = false;
	}
	else {
		isPaused = true;
	}

	UI::Pause();
}

void GameScene::DestroyProjectiles(std::weak_ptr<Projectile> pro)
{
	std::vector<std::shared_ptr<Projectile>>::iterator lok = projectiles.begin();
	while (lok != projectiles.end()) {
		if (*lok == pro.lock()) {
			lok->reset();
			projectiles.erase(lok);
			break;
		}
	}
}

void GameScene::SetGravity(float val)
{
	gravity = val;
}

float GameScene::GetGravity()
{
	return gravity;
}
