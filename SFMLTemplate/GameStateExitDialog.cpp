#include "GameStateExitDialog.h"
#include "Application.h"
#include <assert.h>

namespace ArkanoidGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		data.hintText.setString(L"Вы уверены что хотите завершить эту игру? Enter - Да, Esc - Нет");
		data.hintText.setFont(data.font);
		data.hintText.setCharacterSize(24);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setOrigin(GetTextOrigin(data.hintText, { 0.5f, 0.5f }));

		data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
	}

	void ShutdownGameStateExitDialog(GameStateExitDialogData& data)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(Application::Instance().GetGame());
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, float timeDelta)
	{

	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

		data.background.setSize(windowSize);
		window.draw(data.background);

		data.hintText.setPosition(windowSize / 2.f);
		window.draw(data.hintText);
	}

}