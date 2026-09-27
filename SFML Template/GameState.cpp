#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr)
	{

	}

	void GameState::Init()
	{
		std::cout << "Game State" << std::endl;
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Background"));
	}

	void GameState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}
		}
	}
	void GameState::Update(float dt)
	{

	}
	void GameState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);

		data->window.display();
	}
}