#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	virtual bool OnCreate() = 0;

	virtual void Input() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render(sf::RenderWindow* r_Window) = 0;
	virtual void RenderHUD(sf::RenderWindow* r_Window) = 0;

};
#endif // !SCENE_H

