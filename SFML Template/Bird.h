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

		void Animate(float dt);

		void Update(float dt);

		void Tap();

	private:
		GameDataRef data;

		sf::Sprite* birdSprite;
		std::vector<sf::Texture*> animationFrames;

		unsigned int animationIterator;

		sf::Clock clock;

		sf::Clock movementClock;

		int birdState;
	};
}

