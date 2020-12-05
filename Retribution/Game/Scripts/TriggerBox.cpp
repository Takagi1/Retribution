#include "TriggerBox.h"
#include "../GameObjects/PlayerCharacter.h"
#include "../../Engine/Math/CollisionHandler.h"
#include "../../Engine/Rendering/GameObject.h"
#include "../GameObjects/Projectile.h"
#include "../../Engine/Rendering/SceneGraph.h"

std::vector<std::string> TriggerBox::collisionTags = std::vector<std::string>();

TriggerBox::TriggerBox(PlayerCharacter* parent_, TriggerType triggerType_, glm::vec2 dimention_, glm::vec2 position_) {
	parent = parent_;
	triggerType = triggerType_;

	box = BoundingBox(dimention_, position_);
	

	if (collisionTags.empty()) {
		collisionTags.reserve(1);
		collisionTags.insert(collisionTags.begin(), "Projectile");
	}
}

TriggerBox::~TriggerBox() {
	parent = nullptr;
}

void TriggerBox::Update()
{
	for (auto o : CollisionHandler::GetInstance()->AABBAll(box, collisionTags)) {
		Trigger(o);
		SceneGraph::GetInstance()->RemoveGameObject(o.lock()->GetName());
		break;
	}
}

void TriggerBox::Trigger(std::weak_ptr<GameObject> obj_)
{
	switch (triggerType)
	{
	case TriggerType::Parry:
		parent->ChangeEnergy(dynamic_cast<Projectile*>(obj_.lock().get())->GetPower());
		break;
	case TriggerType::Counter:
		//Damage Monster
		(dynamic_cast<Projectile*>(obj_.lock().get())->DamageParent(parent->GetEnergy() * parent->GetEnergyLevel()));

		//Reset Energy
		parent->ResetEnergy();
	default:
		Debug::FatalError("Invalid TriggerType", "TriggerBox.cpp", __LINE__);
		break;
	}
	parent->SetState(State::Neutral);
}

