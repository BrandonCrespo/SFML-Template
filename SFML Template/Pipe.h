#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace ShowTime
{
	class Pipe
	{
	public:
		Pipe(GameDataRef data);

		void DrawPipes();

	private:
		GameDataRef data;
		std::vector<sf::Sprite*> pipeSprites;
	};
}

