#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../Component.h"
#include "../../Camera/Camera.h"
#include "../../../Engine/Core/Debug.h"


class GUIObject {
public:
	GUIObject(glm::vec2 position_);
	~GUIObject();

	bool OnCreate();
	void Update(const float deltaTime_);
	void Draw(Camera* camera_);

	//Setters

	void SetPosition(glm::vec2 position_);
	void SetRotation(float rotation_);
	void SetScale(glm::vec2 scale_);
	void SetTag(std::string tag_);

	//Gettters

	glm::vec2 GetPosition() const;
	float GetRotation() const;
	glm::vec2 GetScale() const;

	//Do Gui objects need to have a bounding box for this or is there another way to check?
	bool MouseDettection();

	template<typename T>
	inline void AddComponent()
	{
		T* comp = new T();

		//First check to see if it is a child of component
		Component* item = dynamic_cast<Component*>(comp);
		if (item == nullptr) {
			// Cast failed
			Debug::Error("Not child of GUI_Component class", "GUI_Object.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}

		//Next check to see if there is any other component of the same type
		if (GetComponent<T>() != nullptr) {
			Debug::Error("Component of this type is already included", "GUI_Object.h", __LINE__);
			delete item;
			item = nullptr;
			comp = nullptr;
			return;
		}

		item->OnCreate(this);
		guiComponents.push_back(item);
	}

	template<typename T>
	inline T* GetComponent()
	{
		//Loop to find the component
		for (int i = 0; i < guiComponents.size(); i++)
		{
			if (T* ptr = dynamic_cast<T*>(guiComponents[i])) {
				return ptr;
			}
		}
		Debug::Error("Component does not exist", "GUI_Object.h", __LINE__);
		return nullptr;
	}

	template<typename T>
	inline void RemoveComponent() {

		for (int i = 0; i < guiComponents.size(); i++)
		{
			if (dynamic_cast<T*>(guiComponents[i])) {
				delete guiComponents[i];
				guiComponents[i] = nullptr;
				guiComponents.erase(guiComponents.begin() + i);
				return;
			}
		}
		
		Debug::Error("Component does not exist", "GUI_Object.h", __LINE__);
	}
private:
	std::string tag;

	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	std::vector<Component*> guiComponents;
};