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

	//Setters

	void SetPosition(glm::vec2 position_);
	void SetAngle(float angle_);
	void SetScale(glm::vec2 scale_);
	void SetTag(std::string tag_);
	void SetDepth(float depth_);

	//Getters

	glm::vec2 GetPosition() const;
	float GetAngle() const;
	glm::vec2 GetScale() const;
	float GetDepth() const;

	bool MouseDettection();

	template<typename T>
	inline void AddComponent()
	{
		T* comp = new T();

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

		item->OnCreate(this);
		components.push_back(item);
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
private:
	std::string tag;

	//Z is depth
	glm::vec3 position;
	float angle;
	glm::vec2 scale;

	std::vector<Component*> components;


	BoundingBox box;
};