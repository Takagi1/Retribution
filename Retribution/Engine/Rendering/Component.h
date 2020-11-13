#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
public:
	Component() : parent(nullptr), delayUpdate(false) {}
	virtual ~Component() {
		parent = nullptr;
	};
	virtual void Update(const float deltaTime_) = 0;
	
	virtual void Draw() = 0;

	//Get if mouse click is inside the component
	virtual bool FindContainingPoint() = 0;

	bool GetDelayUpdate() const { return delayUpdate; }

	//Use to see if the object already contains components that would cause
	//a conflict if used together (i.e. Physics 2D and Physics 3D cannot be together
	//virtual bool ConflictCheck() = 0;
protected:
	void SetDelayUpdate(const bool delay_) { delayUpdate = delay_; }

	GameObject* parent;

	bool delayUpdate;

};
#endif // !GUI_COMPONENT_H