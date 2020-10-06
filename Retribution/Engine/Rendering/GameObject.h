#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Component.h"
#include "../Camera/Camera.h"
#include "../../Engine/Core/Debug.h"
#include "../Math/BoundingBox.h"


class GameObject {
public:
	GameObject(glm::vec2 position_, float depth_);
	~GameObject();

	bool OnCreate();
	void Update(const float deltaTime_);
	void Draw(Camera* camera_);

	//Movers
	void Translate(glm::vec2 trans_);
	void Rotate(float angle_);


	//Setters

	void SetPosition(glm::vec2 position_);
	void SetAngle(float angle_);
	void SetScale(glm::vec2 scale_);
	void SetName(std::string name_);
	void SetDepth(float depth_);
	void SetTag(std::string tag_);

	//Getters

	glm::vec2 GetPosition() const;
	float GetAngle() const;
	glm::vec2 GetScale() const;
	float GetDepth() const;
	std::string GetTag() const;

	bool MouseDettection();

	BoundingBox GetBoundingBox() const;

	//Used to allow for the direct programing of collision response from objects
	virtual void CollisionResponse(std::vector<GameObject*> obj_) = 0;

	template<typename T, typename Args>
	inline void AddComponent(Args&& args_)
	{
		T* comp = new T(std::forward<Args>(args_));

		//First check to see if it is a child of component
		Component* item = dynamic_cast<Component*>(comp);
		if (item == nullptr) {
			// Cast failed
			Debug::Error("Not child of Component class", "GameObject.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}

		//Next check to see if there is any other component of the same type
		if (GetComponent<T>() != nullptr) {
			Debug::Error("Component of this type is already included", "GameObject.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}
		components.push_back(item);
		Debug::Info("Component created", "GameObject.h", __LINE__);
	}

	template<typename T>
	inline T* GetComponent()
	{
		//Loop to find the component
		for (int i = 0; i < components.size(); i++)
		{
			if (T* ptr = dynamic_cast<T*>(components[i])) {
				return ptr;
			}
		}
		Debug::Error("Component does not exist", "GameObject.h", __LINE__);
		return nullptr;
	}

	template<typename T>
	inline void RemoveComponent() {

		for (int i = 0; i < components.size(); i++)
		{
			if (dynamic_cast<T*>(components[i])) {
				delete components[i];
				components[i] = nullptr;
				components.erase(components.begin() + i);
				return;
			}
		}
		
		Debug::Error("Component does not exist", "GameObject.h", __LINE__);
	}
protected:
	enum class COLLISIONTYPE {
		NONE,
		CONTINUOUS,
		DISCRETE
	};

	void SetCollisionType(COLLISIONTYPE type_);

	//Use this when adding image to 
	void SetBoxScale(glm::vec2 scale_);
private:

	//Used to designate type of object, used for collision exclusion
	std::string tag;

	//name of the object
	std::string name;

	//Z is depth
	glm::vec3 position;
	float angle;
	glm::vec2 scale;

	std::vector<Component*> components;

	BoundingBox box;

	COLLISIONTYPE collisionType;

};