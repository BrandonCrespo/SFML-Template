#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"

namespace ShowTime
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* background;

		Pipe* pipe;
		Land* land;
		Bird* bird;
		Collision collision;
		Flash* flash;

		sf::Clock clock;

		int gameState;
	};
}

