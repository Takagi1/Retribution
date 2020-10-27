#ifndef ARCHER_H
#define ARCHER_H

#include "Monster.h"
#include "../Projectile.h"

class Archer : public Monster
{
public:
	Archer(glm::vec2 position_ = glm::vec2());
	virtual ~Archer();


	bool OnCreate() override;
	virtual void Update(const float deltaTime_);

	void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) override;


private:
	//Making it a shared pointer for memory safety
	std::vector<std::weak_ptr<Projectile>> projectiles;

	void CreateArrow();

	float time;

};
#endif // !ARCHER_H