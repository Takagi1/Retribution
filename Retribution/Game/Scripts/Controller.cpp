#include "Controller.h"
#include "../../Engine/Events/KeyEventListener.h"
#include "../../Engine/Core/CoreEngine.h"

Controller::Controller() : player(nullptr)
{

}

Controller::~Controller()
{
	player = nullptr;
}

bool Controller::OnCreate(PlayerCharacter* player_)
{
	player = player_;
	return true;
}

void Controller::Update(const float deltaTime_)
{
	if (KeyEventListener::keys[SDLK_a]) {
		CoreEngine::GetInstance()->GetCamera()->Translate(glm::vec3(-10.0f, 0, 0));
		//player.SetHealth(1);
		//hud.UpdateHealth(player.GetHealth());
	}
	else if (KeyEventListener::keys[SDLK_d]) {
		CoreEngine::GetInstance()->GetCamera()->Translate(glm::vec3(10.0f, 0, 0));
	}

	if (KeyEventListener::keys[SDLK_w]) {
		CoreEngine::GetInstance()->GetCamera()->Translate(glm::vec3(0.0f, 10.0f, 0));
	}
	else if (KeyEventListener::keys[SDLK_s]) {
		CoreEngine::GetInstance()->GetCamera()->Translate(glm::vec3(0.0f, -10.0f, 0));
	}

	if (KeyEventListener::keys[SDLK_LEFT]) {
		player->Translate(glm::vec2(-1.0f, 0));
	}
	else if (KeyEventListener::keys[SDLK_RIGHT]) {
		if (1 == 0) {
			
		}
		else {
			player->Translate(glm::vec2(1.0f, 0));
		}
	}
}
