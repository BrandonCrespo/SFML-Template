#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"
#include "Game.h"

namespace ShowTime
{
	class HUD
	{
	public:
		HUD(GameDataRef data);

		void Draw();
		void UpdateScore(int score);

	private:
		GameDataRef data;

		sf::Text scoreText;
	};
}

