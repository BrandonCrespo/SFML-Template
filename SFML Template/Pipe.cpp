#include "Pipe.h"
#include <iostream>

namespace ShowTime
{
	Pipe::Pipe(GameDataRef data) : data(data)
	{
		landHeight = data->assets.GetTexture("Land").getSize().y;
		pipeSpawnYOffset = 0;
	}

	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite* sprite(new sf::Sprite(data->assets.GetTexture("Pipe Up")));

		sprite->setPosition(sf::Vector2f(data->window.getSize().x, data->window.getSize().y - sprite->getGlobalBounds().size.y - pipeSpawnYOffset));

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe()
	{
		sf::Sprite* sprite(new sf::Sprite(data->assets.GetTexture("Pipe Down")));

		sprite->setPosition(sf::Vector2f(data->window.getSize().x, -pipeSpawnYOffset));

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite* sprite(new sf::Sprite(data->assets.GetTexture("Pipe Down")));

		sprite->setPosition(sf::Vector2f(data->window.getSize().x, -pipeSpawnYOffset));
		sprite->setColor(sf::Color(0, 0, 0, 0));

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnScoringPipe()
	{
		sf::Sprite* sprite(new sf::Sprite(data->assets.GetTexture("Scoring Pipe")));

		sprite->setPosition(sf::Vector2f(data->window.getSize().x,0));

		scoringPipes.push_back(sprite);
	}

	void Pipe::MovePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			if (pipeSprites.at(i)->getPosition().x < 0 - pipeSprites.at(i)->getGlobalBounds().size.x)
			{
				pipeSprites.erase(pipeSprites.begin() + i);
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;

				pipeSprites.at(i)->move(sf::Vector2f(-movement, 0));
			}
		}

		for (unsigned short int i = 0; i < scoringPipes.size(); i++)
		{
			if (scoringPipes.at(i)->getPosition().x < 0 - scoringPipes.at(i)->getGlobalBounds().size.x)
			{
				scoringPipes.erase(scoringPipes.begin() + i);
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;

				scoringPipes.at(i)->move(sf::Vector2f(-movement, 0));
			}
		}
	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			data->window.draw(*pipeSprites.at(i));
		}
	}

	void Pipe::RandomizePipeOffset()
	{
		pipeSpawnYOffset = rand() % (landHeight + 1);
	}

	const std::vector<sf::Sprite*>& Pipe::GetSprites() const
	{
		return pipeSprites;
	}

	std::vector<sf::Sprite*>& Pipe::GetScoringSprites()
	{
		return scoringPipes;
	}
}