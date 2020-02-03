#pragma once
class UI
{
public:
	UI() {
		font.loadFromFile("OpenSans-Light.ttf");
	}
	~UI();

	void OnCreate();

	static sf::Font font;

	//HUD
	static sf::Text healthDisplay;
	static sf::Text energyDisplay;
	static sf::Text goldDisplay;

	//Pause Menu
	static sf::RectangleShape pauseWindow;


	//TODO::Finish text box to satesfaction
	struct TextBox {
	public:
		bool OnCreate(sf::Vector2f size, sf::Vector2f position) {
			box.setSize(size);
			text.setFont(font);
			text.setFillColor(sf::Color::Black);

			return true;
		}

		void SetText(std::string text_) {
			text.setString(text_);
			unsigned int size = text.getCharacterSize();
			text.setPosition(box.getPosition().x + size / 2, box.getPosition().y + box.getLocalBounds().height / 2);
		}

		sf::Text GetText() {
			return text;
		}
	private:
		sf::RectangleShape box;
		sf::Text text;
	};

	
	static TextBox optionBox;
	static TextBox exitBox;

private:


};

