#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Update(const float deltaTime) = 0;


};

