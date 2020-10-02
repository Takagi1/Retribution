#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Camera;

class Component {
public:
	Component() : parent(nullptr) {}
	virtual ~Component() {
		parent = nullptr;
	};

	virtual bool OnCreate(GameObject* parent_) = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Draw(Camera* camera_) = 0;

	//Get if mouse click is inside the component
	virtual bool FindContainingPoint() = 0;

protected:
	GameObject* parent;

};
#endif // !GUI_COMPONENT_H