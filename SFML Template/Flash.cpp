#include "Flash.h"

namespace ShowTime
{
	Flash::Flash(GameDataRef data) : data(data)
	{
		shape = sf::RectangleShape(sf::Vector2f(data->window.getSize()));
		shape.setFillColor(sf::Color(255, 255, 255, 0));

		flashOn = true;
	}

	void Flash::Show(float dt)
	{
		if (flashOn)
		{
			int alpha = (int)shape.getFillColor().a + (FLASH_SPEED * dt);

			if (alpha >= 255.0f)
			{
				alpha = 255.0f;
				flashOn = false;
			}

			shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = (int)shape.getFillColor().a - (FLASH_SPEED * dt);

			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
				flashOn = false;
			}

			shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::Draw()
	{
		data->window.draw(shape);
	}
}