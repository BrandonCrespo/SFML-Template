#include <sstream>
#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	MainMenuState::MainMenuState(GameDataRef data) :
		data(data)
	{

	}

	void MainMenuState::Init()
	{
		data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Main Menu Background"));
		title = new sf::Sprite(data->assets.GetTexture("Game Title"));
		playButton = new sf::Sprite(data->assets.GetTexture("Play Button"));

		title->setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f) - (title->getGlobalBounds().size.x / 2.f),title->getGlobalBounds().size.y / 2.f));
		playButton->setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f) - (playButton->getGlobalBounds().size.x / 2.f), (SCREEN_HEIGTH / 2) - (playButton->getGlobalBounds().size.y / 2.f)));
	}

	void MainMenuState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*playButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new GameState(data)), true);
			}
		}
	}
	void MainMenuState::Update(float dt)
	{

	}
	void MainMenuState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		data->window.draw(*title);
		data->window.draw(*playButton);

		data->window.display();
	}
}