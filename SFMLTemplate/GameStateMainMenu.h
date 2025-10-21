#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"

namespace ArkanoidGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem difficultyEasy;
		MenuItem difficultyNormal;
		MenuItem difficultyHard;
		MenuItem difficultyInsane;
		MenuItem difficultyImpossible;

		Menu menu;

		sf::SoundBuffer soundBtnHoverBuffer;
		sf::Sound soundBtnHover;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window);
}

