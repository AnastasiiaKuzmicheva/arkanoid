#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	
	struct GameStateExitDialogData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text hintText;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data);
	void ShutdownGameStateExitDialog(GameStateExitDialogData& data);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, const sf::Event& event);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, float timeDelta);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, sf::RenderWindow& window);
}
