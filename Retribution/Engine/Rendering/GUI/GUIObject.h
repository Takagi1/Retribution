#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "GUIComponent.h"
#include "../../Core/Debug.h"


class GUIObject {
public:

	GUIObject(glm::vec2 position_);
	virtual ~GUIObject();

	bool OnCreate(glm::vec2 position_);
	virtual void Update(const float deltaTime_);

	void Draw(Camera* camera);

	glm::vec2 GetPosition() const;
	
	void SetPosition(glm::vec2 position_);
	void SetScale(glm::vec2 scale_);
	void SetName(std::string name_);

	template<typename T, typename Args>
	inline void AddComponent(Args&& args_)
	{
		T* comp = new T(std::forward<Args>(args_));

		//First check to see if it is a child of component
		GUIComponent* item = dynamic_cast<GUIComponent*>(comp);
		if (item == nullptr) {
			// Cast failed
			Debug::Error("Not child of Component class", "GUIObject.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}

		//Next check to see if there is any other component of the same type
		if (GetComponent<T>() != nullptr) {
			Debug::Error("Component of this type is already included", "GUIObject.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}
		components.push_back(item);
		Debug::Info("Component created", "GUIObject.h", __LINE__);
	}

	template<typename T>
	inline T* GetComponent()
	{
		//Loop to find the component
		for (size_t i = 0; i < components.size(); i++)
		{
			if (T* ptr = dynamic_cast<T*>(components[i])) {
				return ptr;
			}
		}
		//TODO: for consideration figure out a way to add in the debug error without it being triggered when adding.
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

		Debug::Error("Component does not exist", "GUIObject.h", __LINE__);
	}

private:

	std::vector<GUIComponent*> components;

	float angle;
	glm::vec2 position, scale;
	std::string name;
};