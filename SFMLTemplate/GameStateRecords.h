#pragma once
#include "GameStateData.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace ArkanoidGame
{
	class GameStateRecordsData : public GameStateData
	{
	public:

		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;

	private:

		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
}