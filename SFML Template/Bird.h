#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"
#include "Game.h"

namespace ShowTime
{
	class Bird
	{
	public:
		Bird(GameDataRef data);

		void Draw();

	private:
		GameDataRef data;

		sf::Sprite* birdSprite;
	};
}

