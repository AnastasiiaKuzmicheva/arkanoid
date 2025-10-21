#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"

namespace ArkanoidGame
{

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;

		MenuItem difficultyItem;
		MenuItem difficultyEasyItem;
		MenuItem difficultyNormalItem;
		MenuItem difficultyHardItem;
		MenuItem difficultyInsaneItem;
		MenuItem difficultyImpossibleItem;

		MenuItem optionsItem;
		MenuItem optionsSoundItem;
		MenuItem optionsMusicItem;

		MenuItem recordsItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
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

