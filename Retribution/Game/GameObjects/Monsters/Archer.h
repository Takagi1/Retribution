#ifndef ARCHER_H
#define ARCHER_H

#include "Monster.h"
#include "../Projectile.h"

class Archer : public Monster
{
public:
	Archer(glm::vec2 position_ = glm::vec2());
	virtual ~Archer();


	bool OnCreate();
	virtual void Update(const float deltaTime_);

	void CollisionResponse(std::vector<GameObject*> obj_) override;


private:
	//Making it a shared pointer for memory safety
	std::vector<std::unique_ptr<Projectile>> projectiles;

	void CreateArrow();

};
#endif // !ARCHER_H