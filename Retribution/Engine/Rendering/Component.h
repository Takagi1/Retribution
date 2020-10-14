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
	virtual void Update(const float deltaTime_) = 0;

	virtual void Draw(Camera* camera) = 0;

	//Get if mouse click is inside the component
	virtual bool FindContainingPoint() = 0;

	//Use to see if the object already contains components that would cause
	//a conflict if used together (i.e. Physics 2D and Physics 3D cannot be together
	//virtual bool ConflictCheck() = 0;
protected:
	GameObject* parent;

};
#endif // !GUI_COMPONENT_H