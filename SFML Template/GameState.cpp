#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"
#include "GameOverState.h"

#include <iostream>

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr),
		pipe(nullptr),
		land(nullptr),
		bird(nullptr),
		flash(nullptr)
	{

	}

	void GameState::Init()
	{
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		data->assets.LoadTexture("Land", LAND_FILEPATH);
		data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		pipe = new Pipe(data);
		land = new Land(data);
		bird = new Bird(data);
		flash = new Flash(data);
		hud = new HUD(data);

		background = new sf::Sprite(data->assets.GetTexture("Game Background"));

		score = 0;
		hud->UpdateScore(score);

		gameState = GameStates::eReady;
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
				if (GameStates::eGameOver != gameState)
				{
					gameState = GameStates::ePlaying;
					bird->Tap();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (GameStates::eGameOver != gameState)
		{
			bird->Animate(dt);
			land->MoveLand(dt);
		}

		if (GameStates::ePlaying == gameState)
		{
			pipe->MovePipes(dt);

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RandomizePipeOffset();

				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				clock.restart();
			}

			bird->Update(dt);

			std::vector<sf::Sprite*> landSprites = land->GetSprites();

			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, *landSprites.at(i), 1.0f))
				{
					gameState = GameStates::eGameOver;

					clock.restart();
				}
			}

			std::vector<sf::Sprite*> pipeSprites = pipe->GetSprites();

			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, *pipeSprites.at(i), 1.0f))
				{
					gameState = GameStates::eGameOver;

					clock.restart();
				}
			}

			if (GameStates::ePlaying == gameState)
			{
				std::vector<sf::Sprite*>& scoringSprites = pipe->GetScoringSprites();

				for (int i = 0; i < scoringSprites.size(); i++)
				{
					if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, *scoringSprites.at(i), 1.0f))
					{
						score++;

						hud->UpdateScore(score);

						scoringSprites.erase(scoringSprites.begin() + i);
					}
				}
			}
		}

		if (GameStates::eGameOver == gameState)
		{
			flash->Show(dt);

			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				data->machine.AddState(StateRef(new GameOverState(data)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		flash->Draw();

		hud->Draw();

		data->window.display();
	}
}