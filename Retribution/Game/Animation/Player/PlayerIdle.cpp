#include "../../../pch.h"
#include "PlayerIdle.h"
#include "../../../Character.h"


PlayerIdle::PlayerIdle()
{
}


PlayerIdle::~PlayerIdle()
{
}

void PlayerIdle::Update(const float deltaTime_, Character* character)
{
	character->hurtBox.SetFillColour(sf::Color::Green);
}

