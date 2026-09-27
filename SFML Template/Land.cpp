#include "Land.h"
#include "DEFINITIONS.h"

namespace ShowTime
{
	Land::Land(GameDataRef data): data(data)
	{
		sf::Sprite* sprite(new sf::Sprite(data->assets.GetTexture("Land")));
		sf::Sprite* sprite2(new sf::Sprite(data->assets.GetTexture("Land")));

		sprite->setPosition(sf::Vector2f(0, data->window.getSize().y - sprite->getGlobalBounds().size.y));
		sprite2->setPosition(sf::Vector2f(sprite2->getGlobalBounds().size.x, data->window.getSize().y - sprite2->getGlobalBounds().size.y));
	
		landSprites.push_back(sprite);
		landSprites.push_back(sprite2);

	}

	void Land::MoveLand(float dt)
	{
		for (unsigned short int i = 0; i < landSprites.size(); i++)
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			landSprites.at(i)->move(sf::Vector2f(-movement, 0.0f));

			if (landSprites.at(i)->getPosition().x < 0 - landSprites.at(i)->getGlobalBounds().size.x)
			{
				sf::Vector2f position(data->window.getSize().x, landSprites.at(i)->getPosition().y);
				
				landSprites.at(i)->setPosition(position);
			}
		}
	}

	void Land::DrawLand()
	{
		for (unsigned short int i = 0; i < landSprites.size(); i++)
		{
			data->window.draw(*landSprites.at(i));
		}
	}
}
