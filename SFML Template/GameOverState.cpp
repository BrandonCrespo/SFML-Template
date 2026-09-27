#include <sstream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "GameState.h"

#include <iostream>

namespace ShowTime
{
	GameOverState::GameOverState(GameDataRef data) :
		data(data),
		background(nullptr),
		gameOverTitle(nullptr),
		gameOverContainer(nullptr),
		retryButton(nullptr)
	{

	}

	void GameOverState::Init()
	{
		data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Over Background"));
		gameOverTitle = new sf::Sprite(data->assets.GetTexture("Game Over Title"));
		gameOverContainer = new sf::Sprite(data->assets.GetTexture("Game Over Body"));
		retryButton = new sf::Sprite(data->assets.GetTexture("Play Button"));

		gameOverContainer->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (gameOverContainer->getGlobalBounds().size.x / 2), (data->window.getSize().y / 2) - (gameOverContainer->getGlobalBounds().size.y / 2)));
		gameOverTitle->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (gameOverTitle->getGlobalBounds().size.x / 2), gameOverContainer->getPosition().y - (gameOverTitle->getGlobalBounds().size.y * 1.2)));
		retryButton->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (retryButton->getGlobalBounds().size.x / 2), gameOverContainer->getPosition().y + gameOverContainer->getGlobalBounds().size.y + (retryButton->getGlobalBounds().size.y * 0.2)));
	}

	void GameOverState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*retryButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new GameState(data)), true);
			}
		}
	}
	void GameOverState::Update(float dt)
	{

	}
	void GameOverState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		data->window.draw(*gameOverTitle);
		data->window.draw(*gameOverContainer);
		data->window.draw(*retryButton);

		data->window.display();
	}
}