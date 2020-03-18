#ifndef SPACIAL_PARTITION_H
#define SPACIAL_PARTITION_H

#include "SFML/Graphics/Rect.hpp"

class Monster;
class Projectile;


//For culling things from draw and collision
class SpacialPartition
{

private:
	SpacialPartition();
	~SpacialPartition();

	static std::unique_ptr<SpacialPartition> partitionInstance;
	friend std::default_delete<SpacialPartition>;
	 
	struct Node
	{
		std::vector<std::weak_ptr<Projectile>> projectileVector;
		std::vector<std::weak_ptr<Monster>> monsterVector;
		std::vector<sf::FloatRect> terrainVector;
	};

	struct Root
	{
		~Root() {
			delete left;
			left = nullptr;
			delete right;
			right = nullptr;
		};
		sf::Vector2f key;
		
		struct Node *left, *right;
	};


	struct Root *NewRoot(sf::Vector2f loc) {
		struct Root *temp = new Root();
		temp->key = loc;
		temp->left = NewNode();
		temp->right = NewNode();
		return temp;
	}


	//Create new Node
	struct Node *NewNode()
	{
		struct Node *temp = new Node();
		temp->monsterVector = std::vector<std::weak_ptr<Monster>>();
		temp->projectileVector = std::vector<std::weak_ptr<Projectile>>();
		temp->terrainVector = std::vector<sf::FloatRect>();
		return temp;
	}
	bool Check(sf::Vector2f loc, sf::Vector2f range, sf::Vector2f pos, sf::Vector2f para);



public:
	SpacialPartition(const SpacialPartition&) = delete;
	SpacialPartition(SpacialPartition&&) = delete;
	SpacialPartition& operator =(const SpacialPartition&) = delete;
	SpacialPartition& operator =(SpacialPartition&&) = delete;

	static SpacialPartition* GetInstance();

	void Init(sf::Vector2f loc);

	void Insert(sf::Vector2f range, std::weak_ptr<Projectile> proj);
	void Insert(sf::Vector2f range, std::weak_ptr<Monster> mon);
	void Insert(sf::Vector2f range, sf::RectangleShape rec);

	std::vector<std::weak_ptr<Projectile>> GetProjectiles() {
		return tree->right->projectileVector;
	}
	std::vector<std::weak_ptr<Projectile>> GetProjectilesOff() {
		return tree->left->projectileVector;
	}
	std::vector<std::weak_ptr<Monster>> GetMonsters() {
		return tree->right->monsterVector;
	}
	std::vector<sf::FloatRect> GetTerrain() {
		return tree->right->terrainVector;
	}

	Root* tree;

};

#endif // !SPACIAL_PARTITION_H