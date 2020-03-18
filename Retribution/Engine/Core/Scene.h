#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	virtual bool OnCreate() = 0;


	/*Input for scene type*/
	virtual void Input(sf::Event inp) = 0;

	virtual void Update(const float deltaTime_) = 0;

	virtual void Render(Window* window) = 0;

	//Camera
	sf::View* view;

};
#endif // !SCENE_H

