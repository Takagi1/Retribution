#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Component.h"
#include "../Camera/Camera.h"
#include "../../Engine/Core/Debug.h"
#include "../Math/BoundingBox.h"
#include "../../Engine/Audio/AudioSource.h"

class GameObject {
public:
	GameObject(glm::vec2 position_, int depth_);
	virtual ~GameObject();

	bool OnCreate();
	virtual void Update(const float deltaTime_);
	void Draw();

	//Movers
	void Translate(glm::vec2 trans_);
	void Rotate(float angle_);


	//Setters

	void SetPosition(glm::vec2 position_);
	void SetAngle(float angle_);
	void SetScale(glm::vec2 scale_);
	void SetName(std::string name_);
	void SetDepth(const int depth_);
	void SetTag(std::string tag_);

	//Getters

	glm::vec2 GetPosition() const;
	float GetAngle() const;
	glm::vec2 GetScale() const;
	int GetDepth() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;
	std::string GetName() const;

	bool MouseDettection();

	//Used to allow for the direct programing of collision response from objects
	virtual void CollisionResponse(std::vector<std::weak_ptr<GameObject>> obj_) = 0;


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
		
		Debug::Error("Component does not exist", "GameObject.h", __LINE__);
	}

	AudioSource* sound;

protected:

	void UpdateBoundingBox(BoundingBox box_);

private:

	//Used to designate type of object, used for collision exclusion
	std::string tag;

	//name of the object
	std::string name;

	glm::vec2 position;
	float angle;
	glm::vec2 scale;
	int depth;

	std::vector<Component*> components;

	BoundingBox box;





};
#endif // !GAMEOBJECT_H