#include "../../../pch.h"
#include "TextBox.h"
#include "../UI.h"


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
	text.setCharacterSize(20);

	return true;
}

void TextBox::SetText(std::string text_) {
	text.setString(text_);
	float sizeW = text.getGlobalBounds().width / 2;
	float sizeH = text.getGlobalBounds().height / 2;
	text.setPosition(box.getGlobalBounds().left + (box.getGlobalBounds().width / 2) - sizeW, box.getGlobalBounds().top + (box.getGlobalBounds().height / 2) - sizeH);
}

sf::Vector2f TextBox::GetSize() const
{
	float a = text.getGlobalBounds().width;
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

void TextBox::Draw(Window * window) {
	window->GetWindow()->draw(box);
	window->GetWindow()->draw(text);
}