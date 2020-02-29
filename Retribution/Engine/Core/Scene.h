#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	virtual bool OnCreate() = 0;

	virtual void Input() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render(Window* window) = 0;

	//Camera
	sf::View* view;

};
#endif // !SCENE_H

