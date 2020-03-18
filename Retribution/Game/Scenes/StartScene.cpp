#include "../../pch.h"
#include "StartScene.h"
#include "../UI/UI.h"

StartScene::StartScene() : Scene()
{

}


StartScene::~StartScene()
{

}

bool StartScene::OnCreate()
{
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	
	view = new sf::View(sf::FloatRect(sf::Vector2f(0, 0), Options::GetResolution()));

	title.setString("Retribution");
	title.setFont(UI::font);
	title.setPosition(800, 200);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(60);

	//TODO: Add Scale variable?
	float x = Options::GetResolution().x / 1920;
	float y = Options::GetResolution().y / 1080;


	//TODO: fix offset because resolution in not right on create
	TextBox textbox;

	textbox.OnCreate(sf::Vector2f(200, 100), sf::Vector2f(880 * x, 320 * y));

	textbox.Select();
	textbox.SetText("New Game");

	textBoxs[0] = textbox;

	textbox.OnCreate(sf::Vector2f(200, 100), sf::Vector2f(880 * x, 500 * y));

	textbox.Deselect();
	textbox.SetText("Exit");

	textBoxs[1] = textbox;

	return true;
}

void StartScene::Input(sf::Event input)
{
	switch (input.type)
	{
	case sf::Event::KeyPressed:
		if (input.key.code == sf::Keyboard::W) {
			MoveMenu(-1);
		}
		else if (input.key.code == sf::Keyboard::S) {
			MoveMenu(1);
		}
		else if (input.key.code == sf::Keyboard::X) {
			CallFunction();
		}
		break;
	default:
		break;
	}
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render(Window* window)
{
	window->Clear();

	window->GetWindow()->draw(title);

	for (auto& all : textBoxs) {
		all.Draw(window);
	}

	window->Display();
}

void StartScene::MoveMenu(int val)
{
	if (counter + val < 0 || counter + val == 3) { return; }

	textBoxs[counter].Deselect();
	counter += val;

	textBoxs[counter].Select();
}

void StartScene::CallFunction()
{
	if (counter == 0) {
		Engine::GetInstance()->SetCurrentScene(1);
	}
	else if (counter == 1) {
		Engine::GetInstance()->Exit();
	}
}
