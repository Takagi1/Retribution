#include "../../pch.h"
#include "UI.h"
#include "Menu/PauseMenu.h"
#include "../../PlayerCharacter.h"


sf::Font UI::font = sf::Font();
sf::Text UI::healthDisplay = sf::Text();
sf::Text UI::energyDisplay = sf::Text();
sf::RectangleShape UI::pauseWindow = sf::RectangleShape();
std::unique_ptr<InteractiveMenu> UI::pauseMenu = std::unique_ptr<InteractiveMenu>();
UI::Menu UI::menu = Menu();
sf::Text UI::fpsCounter = sf::Text();

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
	float x = Options::GetResolution().x / 1920;
	float y = Options::GetResolution().y / 1080;

	menu = DEFAULT;

	//Setup HUD
	healthDisplay.setFont(font);
	healthDisplay.setPosition(sf::Vector2f(0, 200 * y));
	healthDisplay.setFillColor(sf::Color::Black);

	energyDisplay.setFont(font);
	energyDisplay.setPosition(sf::Vector2f(0, 300 * y));
	energyDisplay.setFillColor(sf::Color::Black);

	pauseWindow.setSize(sf::Vector2f((x * 1920) / 2, (y * 1080) / 2));
	pauseWindow.setPosition(960 * x, 540 * y);
	pauseWindow.move(-pauseWindow.getSize().x / 2, -pauseWindow.getSize().y / 2);
	pauseWindow.setFillColor(sf::Color::Red);
	pauseWindow.setOutlineColor(sf::Color::Black);
	pauseWindow.setOutlineThickness(3);

	pauseMenu = std::make_unique<PauseMenu>();

	fpsCounter.setFont(UI::font);
	fpsCounter.setFillColor(sf::Color::Black);
	fpsCounter.setPosition(50, 0);
	fpsCounter.setString("FPS: 0");
}

void UI::Update(const float deltaTime_)
{
	healthDisplay.setString("Health: " + std::to_string(PlayerCharacter::GetHealth()));

	energyDisplay.setString("Energy: " + std::to_string(PlayerCharacter::GetEnergy()));
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

void UI::Draw(Window * window)
{
	window->GetWindow()->draw(healthDisplay);
	window->GetWindow()->draw(energyDisplay);

	switch (menu)
	{
	case UI::PAUSEMENU:
		window->GetWindow()->draw(pauseWindow);
		pauseMenu->Draw(window);
		break;
	default:
		break;
	}
}

void UI::Pause()
{
	if (menu != PAUSEMENU) {
		menu = PAUSEMENU;
	}
	else {
		menu = DEFAULT;
	}
}
