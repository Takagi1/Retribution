#pragma once

#include "../../Engine/Math/BoundingBox.h"
#include <string>
#include <memory>
#include <vector>

class GameObject;
class PlayerCharacter;

enum class TriggerType {
	//Parry
	Parry = 0,

	//Counter
	Counter = 1
};

class TriggerBox {
public: 
	TriggerBox(PlayerCharacter* parent_, TriggerType triggerType_, glm::vec2 dimention_, glm::vec2 position_);
	~TriggerBox();

	void Update();

	//Result method
	void Trigger(std::weak_ptr<GameObject> obj_);

private:
	PlayerCharacter* parent;

	BoundingBox box;

	TriggerType triggerType;

	static std::vector<std::string> collisionTags;
};