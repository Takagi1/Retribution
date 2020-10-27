#pragma once

#include "../../Engine/Math/BoundingBox.h"
#include <string>
#include <memory>

class GameObject;
class PlayerCharacter;

class TriggerBox {
public: 
	TriggerBox(PlayerCharacter* parent_, std::string triggerType_, glm::vec2 dimention_, glm::vec2 position_);
	~TriggerBox();

	void Update();

	//Result method
	void Trigger(std::weak_ptr<GameObject> obj_);

private:
	PlayerCharacter* parent;

	BoundingBox box;

	std::string triggerType;


};