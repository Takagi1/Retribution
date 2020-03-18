#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../../../Engine/Core/Window.h"

//TODO: Scale text to the box
class TextBox
{
public:
	TextBox();
	~TextBox();

	bool OnCreate(sf::Vector2f size, sf::Vector2f position);

	void SetText(std::string text_);

	sf::Vector2f GetSize() const;
	
	void Select();
	void Deselect();

	void Draw(Window* window);
private:
	sf::RectangleShape box;
	sf::Text text;

	float scaleX;
	float scaleY;

};

#endif // !TEXTBOX_H
