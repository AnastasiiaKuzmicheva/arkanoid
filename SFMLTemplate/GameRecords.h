#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace ArkanoidGame
{
	class Game;

	class GameStateRecordsData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

}
