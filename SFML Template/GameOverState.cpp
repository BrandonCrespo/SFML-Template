#include <sstream>
#include "GameOverState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	GameOverState::GameOverState(GameDataRef data) :
		data(data),
		background(nullptr)
	{

	}

	void GameOverState::Init()
	{
		data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Over Background"));
	}

	void GameOverState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
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

		data->window.display();
	}
}