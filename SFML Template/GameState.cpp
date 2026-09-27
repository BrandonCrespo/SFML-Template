#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr),
		pipe(nullptr),
		land(nullptr)
	{

	}

	void GameState::Init()
	{
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		data->assets.LoadTexture("Land", LAND_FILEPATH);

		pipe = new Pipe(data);
		land = new Land(data);

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


			}
		}
	}

	void GameState::Update(float dt)
	{
		pipe->MovePipes(dt);
		land->MoveLand(dt);

		if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			pipe->RandomizePipeOffset();

			pipe->SpawnInvisiblePipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnTopPipe();

			clock.restart();
		}
	}

	void GameState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		pipe->DrawPipes();
		land->DrawLand();

		data->window.display();
	}
}