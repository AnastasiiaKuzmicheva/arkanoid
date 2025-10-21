#include "GameStateGameOver.h"
#include "Application.h"
#include <assert.h>
#include "Application.h"
#include <sstream>

namespace ArkanoidGame
{
	const char* PLAYER_NAME = "Player";

	void InitGameStateGameOver(GameStateGameOverData& data)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		data.timeSinceGameOver = 0.f;

		data.gameOverText.setFont(data.font);
		data.gameOverText.setCharacterSize(48);
		data.gameOverText.setStyle(sf::Text::Bold);
		data.gameOverText.setFillColor(sf::Color::Red);
		data.gameOverText.setString(L"Вы проиграли");
		data.gameOverText.setOrigin(GetTextOrigin(data.gameOverText, { 0.5f, 0.5f }));

		data.hintText.setFont(data.font);
		data.hintText.setCharacterSize(24);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setString(L"Нажмите Space для перезапуска");
		data.hintText.setOrigin(GetTextOrigin(data.hintText, { 0.5f, 1.f }));

		data.recordsTableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		int snakeScores = Application::Instance().GetGame().recordsTable[PLAYER_NAME];
		for (const auto& item : Application::Instance().GetGame().recordsTable)
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isSnakeInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			data.recordsTableTexts.emplace_back(); // Create text in place
			sf::Text& text = data.recordsTableTexts.back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setCharacterSize(24);
			if (it->second == PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isSnakeInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		// If snake is not in table, replace last element with him
		if (!isSnakeInTable)
		{
			sf::Text& text = data.recordsTableTexts.back();
			std::stringstream sstream;
			sstream << MAX_RECORDS_TABLE_SIZE << ". " << PLAYER_NAME << ": " << snakeScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, float timeDelta)
	{
		data.timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.gameOverText.setFillColor(gameOverTextColor);
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 150.f);
		window.draw(data.gameOverText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.recordsTableTexts.size());
		for (auto& text : data.recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE; ++i)
		{
			data.recordsTableTexts[i].setOrigin(GetTextOrigin(data.recordsTableTexts[i], { 0.5f, 0.f }));
			data.recordsTableTexts[i].setPosition(window.getSize().x / 2.f, 200 + i * 50.f);

			window.draw(data.recordsTableTexts[i]);
		}
		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 10.f);
		window.draw(data.hintText);
	}
}