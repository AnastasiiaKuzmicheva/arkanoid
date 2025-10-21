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

	void ShutdownGameStateRecords(GameStateRecordsData& data);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, const sf::Event& event);
	void InitGameRecord(GameStateRecordsData& data);
	void UpdateGameStateRecords(GameStateRecordsData& data, float timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, sf::RenderWindow& window);
}
