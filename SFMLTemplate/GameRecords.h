#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace ArkanoidGame
{
	struct Game;

	struct GameStateRecordsData
	{
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event);
	void InitGameRecord(GameStateRecordsData& data, Game& game);
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}
