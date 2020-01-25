#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() {
		font.loadFromFile("OpenSans-Light.ttf");
	};

	sf::Font font;

	virtual bool OnCreate() = 0;

	virtual void Input() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
	virtual void RenderHUD() = 0;

};
#endif // !SCENE_H

