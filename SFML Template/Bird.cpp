#include "Bird.h"

namespace ShowTime
{
	Bird::Bird(GameDataRef data) : 
		data(data),
		birdSprite(nullptr)
	{
		birdSprite = new sf::Sprite(this->data->assets.GetTexture("Bird Frame 1"));
	}

	void Bird::Draw()
	{
		data->window.draw(*birdSprite);
	}
}
