#include "pch.h"
#include "SpacialPartition.h"
#include "Projectile.h";
#include "Game/Monsters/Monster.h"
#include <algorithm>

std::unique_ptr<SpacialPartition> SpacialPartition::partitionInstance = nullptr;

SpacialPartition * SpacialPartition::GetInstance()
{
	if (partitionInstance.get() == nullptr) {
		partitionInstance.reset(new SpacialPartition);
	}
	return partitionInstance.get();
}

void SpacialPartition::Init(sf::Vector2f loc)
{
	delete tree;
	tree = nullptr;
	tree = NewRoot(loc);
}

SpacialPartition::SpacialPartition()
{

}


SpacialPartition::~SpacialPartition()
{
}

bool SpacialPartition::Check(sf::Vector2f loc, sf::Vector2f range, sf::Vector2f pos, sf::Vector2f para)
{
	if (loc.x - range.x > pos.x + para.x ||
		loc.y - range.y > pos.y + para.y ||
		loc.x + range.x < pos.x ||
		loc.y + range.y < pos.y) {
		return false;
	}

	return true;
}

void SpacialPartition::Insert(sf::Vector2f range, std::weak_ptr<Projectile> proj)
{
	if (Check(tree->key, range, proj.lock()->hurtBox.GetPosition(), proj.lock()->hurtBox.GetSize())) {
		tree->right->projectileVector.push_back(proj);
	}
	else {
		tree->left->projectileVector.push_back(proj);
	}
}

void SpacialPartition::Insert(sf::Vector2f range, std::weak_ptr<Monster> mon)
{
	if (Check(tree->key, range, mon.lock()->hurtBox.GetPosition(), mon.lock()->hurtBox.GetSize())) {
		tree->right->monsterVector.push_back(mon);
	}
	else {
		tree->left->monsterVector.push_back(mon);
	}
}

void SpacialPartition::Insert(sf::Vector2f range, sf::RectangleShape rec)
{
	sf::FloatRect rect = rec.getGlobalBounds();

	tree->right->a = 1;
	if (Check(tree->key, range, rec.getPosition(), rec.getSize())) {
		tree->right->groundVector.push_back(rect);
	}
	else {
		tree->left->groundVector.push_back(rect);
	}
}
