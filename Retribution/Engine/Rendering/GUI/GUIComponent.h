#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

class GUIObject;
class Camera;

class GUIComponent {
public:
	GUIComponent() : parent(nullptr) {}
	virtual ~GUIComponent() {
		parent = nullptr;
	};

	virtual void Update(const float deltaTime_) = 0;
	virtual void Draw(Camera* camera_) = 0;

	//Get if mouse click is inside the component
	virtual bool FindContainingPoint() = 0;

protected:
	GUIObject* parent;

};
#endif // !GUI_COMPONENT_H