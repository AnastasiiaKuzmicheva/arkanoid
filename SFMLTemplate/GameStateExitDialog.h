#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	
	class GameStateExitDialogData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::RectangleShape background;
		sf::Text hintText;
	};
}
