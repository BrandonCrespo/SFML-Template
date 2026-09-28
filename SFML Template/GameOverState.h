#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int score);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* background;

		sf::Sprite* gameOverTitle;
		sf::Sprite* gameOverContainer;
		sf::Sprite* retryButton;
		sf::Sprite* medal;

		sf::Text scoreText;
		sf::Text highScoreText;

		int score;
		int highscore;
	};
}

