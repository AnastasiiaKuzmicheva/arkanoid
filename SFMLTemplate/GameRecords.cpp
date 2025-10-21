#include "GameRecords.h"
#include "Game.h"
#include "Constants.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void InitGameRecord(GameStateRecordsData& data, Game& game)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		data.titleText.setString(L"Рекорды");
		data.titleText.setFont(data.font);
		data.titleText.setFillColor(sf::Color::Red);
		data.titleText.setCharacterSize(30);

		data.tableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::map<int, std::string> sortedRecordsTable;
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			data.tableTexts.emplace_back(); // Create text in place
			sf::Text& text = data.tableTexts.back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}
	}

	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		// Nothing to clear here
	}

	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
		}
	}

	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window)
	{
		data.titleText.setOrigin(GetTextOrigin(data.titleText, { 0.5f, 0.f }));
		data.titleText.setPosition(window.getSize().x / 2.f, 100.0f);
		window.draw(data.titleText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.tableTexts.size());

		for (auto& text : data.tableTexts)
		{
			textsList.push_back(&text);
		}

		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE; ++i)
		{
			data.tableTexts[i].setOrigin(GetTextOrigin(data.tableTexts[i], { 0.5f, 0.f }));
			data.tableTexts[i].setPosition(window.getSize().x / 2.f, 150 + i * 50.f);

			window.draw(data.tableTexts[i]);
		}
	}
}

