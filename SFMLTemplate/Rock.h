#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ArkanoidGame
{
	struct Rock
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitRock(Rock& rock, const sf::Texture& texture);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}