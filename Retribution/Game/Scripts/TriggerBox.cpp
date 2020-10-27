#include "TriggerBox.h"
#include "../GameObjects/PlayerCharacter.h"
#include "../../Engine/Math/CollisionHandler.h"
#include "../../Engine/Rendering/GameObject.h"
#include "../GameObjects/Projectile.h"
#include "../../Engine/Rendering/SceneGraph.h"

TriggerBox::TriggerBox(PlayerCharacter* parent_, std::string triggerType_, glm::vec2 dimention_, glm::vec2 position_) {
	parent = parent_;
	triggerType = triggerType_;

	box = BoundingBox(dimention_, position_);
}

TriggerBox::~TriggerBox() {
	parent = nullptr;
}

void TriggerBox::Update()
{
	std::vector<std::weak_ptr<GameObject>> om = CollisionHandler::GetInstance()->AABB(box);
	for (auto o : om) {
		if (o.lock()->GetTag() == "Projectile") {
			Trigger(o);
			SceneGraph::GetInstance()->RemoveGameObject(o.lock()->GetName());
			break;
		}
	}
}

void TriggerBox::Trigger(std::weak_ptr<GameObject> obj_)
{
	//Dynamicly cast to Projectile

	if (triggerType == "Parry") {
		parent->ChangeEnergy(dynamic_cast<Projectile*>(obj_.lock().get())->GetPower());
		//SceneGraph::GetInstance()->RemoveGameObject(obj_.lock()->GetName());
		return;
	}
	else if (triggerType == "Counter") {
		return;
	}

}

