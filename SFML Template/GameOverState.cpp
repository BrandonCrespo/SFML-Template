#include <sstream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "GameState.h"

#include <iostream>
#include <fstream>

namespace ShowTime
{
	GameOverState::GameOverState(GameDataRef data, int score) :
		data(data),
		background(nullptr),
		gameOverTitle(nullptr),
		gameOverContainer(nullptr),
		retryButton(nullptr),
		score(score),
		scoreText(data->assets.GetFont("Flappy Font")),
		highScoreText(data->assets.GetFont("Flappy Font"))
	{

	}

	void GameOverState::Init()
	{
		std::ifstream readFile;
		readFile.open(HIGHSCORE_FILEPATH);

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highscore;
			}
		}

		readFile.close();

		std::ofstream writeFile(HIGHSCORE_FILEPATH);

		if (writeFile.is_open())
		{
			if (score > highscore)
			{
				highscore = score;
			}
			writeFile << highscore;
		}
		writeFile.close();

		data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);

		data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Over Background"));
		gameOverTitle = new sf::Sprite(data->assets.GetTexture("Game Over Title"));
		gameOverContainer = new sf::Sprite(data->assets.GetTexture("Game Over Body"));
		retryButton = new sf::Sprite(data->assets.GetTexture("Play Button"));

		gameOverContainer->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (gameOverContainer->getGlobalBounds().size.x / 2), (data->window.getSize().y / 2) - (gameOverContainer->getGlobalBounds().size.y / 2)));
		gameOverTitle->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (gameOverTitle->getGlobalBounds().size.x / 2), gameOverContainer->getPosition().y - (gameOverTitle->getGlobalBounds().size.y * 1.2)));
		retryButton->setPosition(sf::Vector2f((data->window.getSize().x / 2) - (retryButton->getGlobalBounds().size.x / 2), gameOverContainer->getPosition().y + gameOverContainer->getGlobalBounds().size.y + (retryButton->getGlobalBounds().size.y * 0.2)));
		
		scoreText.setString(std::to_string(score));
		scoreText.setCharacterSize(56);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().size.x / 2, scoreText.getGlobalBounds().size.y / 2));
		scoreText.setPosition(sf::Vector2f(data->window.getSize().x / 10 * 7.25, data->window.getSize().y / 2.15));
	
		highScoreText.setString(std::to_string(highscore));
		highScoreText.setCharacterSize(56);
		highScoreText.setFillColor(sf::Color::White);
		highScoreText.setOrigin(sf::Vector2f(highScoreText.getGlobalBounds().size.x / 2, highScoreText.getGlobalBounds().size.y / 2));
		highScoreText.setPosition(sf::Vector2f(data->window.getSize().x / 10 * 7.25, data->window.getSize().y / 1.78));
	
		if (score >= PLATINUM_MEDAL_SCORE)
		{
			medal = new sf::Sprite(data->assets.GetTexture("Platinum Medal"));
		}
		else if (score >= GOLD_MEDAL_SCORE)
		{
			medal = new sf::Sprite(data->assets.GetTexture("Gold Medal"));
		}
		else if (score >= SILVER_MEDAL_SCORE)
		{
			medal = new sf::Sprite(data->assets.GetTexture("Silver Medal"));
		}
		else if (score >= BRONZE_MEDAL_SCORE)
		{
			medal = new sf::Sprite(data->assets.GetTexture("Bronze Medal"));
		}
		else
		{
			medal = new sf::Sprite(data->assets.GetTexture("Bronze Medal"));
			medal->setColor(sf::Color(0, 0, 0, 0));
		}

		medal->setPosition(sf::Vector2f(175, 465));
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
		data->window.draw(scoreText);
		data->window.draw(highScoreText);

		data->window.draw(*medal);

		data->window.display();
	}
}