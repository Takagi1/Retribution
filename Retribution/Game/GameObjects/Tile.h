#pragma once

#include "../../Engine/Rendering/GameObject.h"

class Tile : public GameObject {

public: 
	Tile();
	~Tile();

	bool OnCreate(glm::vec2 position_);

	virtual void Update(const float deltaTime_);

	//Used to allow for the direct programing of collision response from objects
	virtual void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_);
};