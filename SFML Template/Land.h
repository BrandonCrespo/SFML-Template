#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace ShowTime
{
	class Land
	{
	public:
		Land(GameDataRef data);

		void MoveLand(float dt);
		void DrawLand();

	private:
		GameDataRef data;

		std::vector<sf::Sprite*> landSprites;
	};
}

