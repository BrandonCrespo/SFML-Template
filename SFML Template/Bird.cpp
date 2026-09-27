#include "Bird.h"

namespace ShowTime
{
	Bird::Bird(GameDataRef data) : 
		data(data),
		birdSprite(nullptr)
	{
		animationIterator = 0;
		animationFrames.push_back(new sf::Texture(this->data->assets.GetTexture("Bird Frame 1")));
		animationFrames.push_back(new sf::Texture(this->data->assets.GetTexture("Bird Frame 2")));
		animationFrames.push_back(new sf::Texture(this->data->assets.GetTexture("Bird Frame 3")));
		animationFrames.push_back(new sf::Texture(this->data->assets.GetTexture("Bird Frame 4")));
		birdSprite = new sf::Sprite(*animationFrames.at(animationIterator));
	}

	void Bird::Draw()
	{
		data->window.draw(*birdSprite);
	}

	void Bird::Animate(float dt)
	{
		if (clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / animationFrames.size())
		{
			if (animationIterator < animationFrames.size() - 1)
			{
				animationIterator++;
			}
			else
			{
				animationIterator = 0;
			}

			delete birdSprite;
			birdSprite = new sf::Sprite(*animationFrames.at(animationIterator));

			clock.restart();
		}
	}
}
