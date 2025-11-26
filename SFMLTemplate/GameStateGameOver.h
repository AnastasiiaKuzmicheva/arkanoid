#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameOverData : public GameStateData
	{
	public:
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;

	private:

		sf::Font font;
		float timeSinceGameOver = 0.f;

		// UI data
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	};

}