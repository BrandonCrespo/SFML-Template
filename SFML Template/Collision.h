#pragma once

#include <SFML/Graphics.hpp>

namespace ShowTime
{
	class Collision
	{
	public:
		Collision();

		bool CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
	};
}

