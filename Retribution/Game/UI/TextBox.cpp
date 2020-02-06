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
	unsigned int sizeW = text.getGlobalBounds().width  / 2;
	unsigned int sizeH = text.getGlobalBounds().height / 2;
	text.setPosition(box.getGlobalBounds().left + (box.getGlobalBounds().width / 2) - sizeW, box.getGlobalBounds().top + (box.getGlobalBounds().height / 2) - sizeH);
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