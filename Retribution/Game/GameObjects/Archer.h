#ifndef ARCHER_H
#define ARCHER_H

#include "../../Engine/Rendering/GameObject.h"
#include "Projectile.h"

class Archer : public GameObject
{
public:
	Archer(glm::vec2 position_ = glm::vec2());
	virtual ~Archer();


	bool OnCreate();
	virtual void Update(const float deltaTime_);


private:
	//Making it a shared pointer for memory safety
	std::vector<std::shared_ptr<Projectile>> projectiles;

	void CreateArrow();

};
#endif // !ARCHER_H