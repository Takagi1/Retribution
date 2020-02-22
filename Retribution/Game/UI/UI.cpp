#include "../../pch.h"
#include "UI.h"
#include "Menu/PauseMenu.h"


sf::Font UI::font = sf::Font();
sf::Text UI::healthDisplay = sf::Text();
sf::Text UI::energyDisplay = sf::Text();
sf::Text UI::goldDisplay = sf::Text();
sf::RectangleShape UI::pauseWindow = sf::RectangleShape();
std::unique_ptr<InteractiveMenu> UI::pauseMenu = std::unique_ptr<InteractiveMenu>();
UI::Menu UI::menu = Menu();

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
	float x = Options::display.resolution.x / 1920;
	float y = Options::display.resolution.y / 1080;

	menu = PAUSEMENU;

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
	pauseWindow.setOutlineColor(sf::Color::Black);
	pauseWindow.setOutlineThickness(3);

	pauseMenu = std::make_unique<PauseMenu>();
}

void UI::Update(const float deltaTime_)
{
}

void UI::Scroll(int val_)
{
	switch (menu)
	{

	case UI::PAUSEMENU:
		pauseMenu->MoveMenu(val_);
		break;
	default:
		break;
	}
}

void UI::CallFunction()
{
	switch (menu)
	{

	case UI::PAUSEMENU:
		pauseMenu->CallFunction();
		break;
	default:
		break;
	}
}

void UI::Draw(sf::RenderWindow * r_Window)
{
	switch (menu)
	{
	case UI::PAUSEMENU:
		pauseMenu->Draw(r_Window);
		break;
	default:
		break;
	}
}
