#include "../../pch.h"
#include "TextBox.h"
#include "UI.h"


TextBox::TextBox()
{

}


TextBox::~TextBox()
{
}

bool TextBox::OnCreate(sf::Vector2f size, sf::Vector2f position)
{
	box.setSize(size);
	box.setPosition(position);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(3);
	text.setFont(UI::font);
	text.setFillColor(sf::Color::Black);

	return true;
}

void TextBox::SetText(std::string text_) {
	text.setString(text_);
	unsigned int size = text.getCharacterSize();
	text.setPosition(box.getPosition().x + (box.getLocalBounds().width / 2) - size / 2, box.getPosition().y + box.getLocalBounds().height / 2);
}

sf::Vector2f TextBox::GetSize() const
{
	return box.getSize();
}

void TextBox::Select()
{
	box.setFillColor(sf::Color::Blue);
}

void TextBox::Deselect()
{
	box.setFillColor(sf::Color::White);
}

void TextBox::Draw(sf::RenderWindow * r_Window) {
	r_Window->draw(box);
	r_Window->draw(text);
}