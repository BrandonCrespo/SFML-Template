#include "Collision.h"

namespace ShowTime
{
	Collision::Collision()
	{

	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		if (rect1.findIntersection(rect2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
	{
		sprite1.setScale(sf::Vector2f(scale1, scale1));
		sprite2.setScale(sf::Vector2f(scale2, scale2));

		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		if (rect1.findIntersection(rect2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}