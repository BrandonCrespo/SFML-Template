#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr),
		pipe(nullptr)
	{

	}

	void GameState::Init()
	{
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);

		pipe = new Pipe(data);

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

			if (data->input.IsSpriteClicked(*background, sf::Mouse::Button::Left, data->window))
			{
				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();

			}
		}
	}

	void GameState::Update(float dt)
	{
		pipe->MovePipes(dt);
	}

	void GameState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		pipe->DrawPipes();

		data->window.display();
	}
}