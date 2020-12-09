#include "Controller.h"
#include "../../Engine/Events/KeyEventListener.h"
#include "../../Engine/Core/CoreEngine.h"

Controller::Controller() : player(std::weak_ptr<PlayerCharacter>())
{

}

Controller::~Controller()
{
}

bool Controller::OnCreate(std::weak_ptr<PlayerCharacter> player_)
{
	player = player_;
	return true;
}

void Controller::Update(const float deltaTime_)
{
	//Manual Camera control
	if (KeyEventListener::keys[SDLK_a]) {
		CoreEngine::GetInstance()->GetCamera()->Translate(glm::vec3(-10.0f, 0, 0));
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
		if (player.lock()->GetState() == State::Neutral) {
			player.lock()->Move(-1, 0);
		}
	}
	else if (KeyEventListener::keys[SDLK_RIGHT]) {
		if (player.lock()->GetState() == State::Neutral) {
			player.lock()->Move(1, 0);
		}
	}

	if (KeyEventListener::keys[SDLK_x]) {
		if (player.lock()->GetState() == State::Neutral) {
			player.lock()->Parry();
		}
	}

	if (KeyEventListener::keys[SDLK_z]) {
		if (player.lock()->GetState() == State::Neutral) {
			player.lock()->Counter();
		}
	}

	//TODO: make it only one press that cause's this.
	if (KeyEventListener::keys[SDLK_p]) {
		SceneGraph::GetInstance()->Pause();
	}
}
