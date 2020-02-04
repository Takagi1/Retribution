#include "../../pch.h"
#include "UI.h"


sf::Font UI::font = sf::Font();
sf::Text UI::healthDisplay = sf::Text();
sf::Text UI::energyDisplay = sf::Text();
sf::Text UI::goldDisplay = sf::Text();
sf::RectangleShape UI::pauseWindow = sf::RectangleShape();
UI::TextBox UI::optionBox = UI::TextBox();
UI::TextBox UI::exitBox = UI::TextBox();

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init()
{
	font.loadFromFile("OpenSans-Light.ttf");

	//Hold resolution here to not have to keep accessing it 
	float x = Engine::GetInstance()->resolution.x / 1920;
	float y = Engine::GetInstance()->resolution.y / 1080;

	//Setup HUD
	healthDisplay.setFont(font);
	healthDisplay.setPosition(sf::Vector2f(0, 200 * y));
	healthDisplay.setFillColor(sf::Color::Black);

	energyDisplay.setFont(font);
	energyDisplay.setPosition(sf::Vector2f(0, 300 * y));
	energyDisplay.setFillColor(sf::Color::Black);

	goldDisplay.setFont(font);
	goldDisplay.setPosition(sf::Vector2f(0, 400 * y));
	goldDisplay.setFillColor(sf::Color::Black);

	pauseWindow.setSize(sf::Vector2f((x * 1920) / 2, (y * 1080) / 2));
	pauseWindow.setPosition(960 * x, 540 * y);
	pauseWindow.move(-pauseWindow.getSize().x / 2, -pauseWindow.getSize().y / 2);
	pauseWindow.setFillColor(sf::Color::Red);

	//TODO:: Centre Text
	optionBox.OnCreate(sf::Vector2f(200, 100),
		sf::Vector2f(pauseWindow.getPosition().x + (pauseWindow.getGlobalBounds().width / 2) - 100,
			pauseWindow.getPosition().y + 50));

	optionBox.SetText("Options");

	exitBox.OnCreate(sf::Vector2f(200, 100),
		sf::Vector2f(pauseWindow.getPosition().x + (pauseWindow.getGlobalBounds().width / 2) - 100,
			pauseWindow.getPosition().y + 200));

	exitBox.SetText("Exit");
}
