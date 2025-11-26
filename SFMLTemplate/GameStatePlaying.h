#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ball.h"
#include "Platform.h"


namespace ArkanoidGame
{
	class Game;
	class Block;

	class GameStatePlayingData : public GameStateData
	{
	public:

		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;

	private:

		void createBlocks();
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX,
			bool& needInverseDirY);
		//Resources
		sf::Texture platformTexture;
		sf::Texture ballTexture;
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		std::vector<std::shared_ptr<Block>> blocks;

		int score = 0;
		// UI data
		sf::Font font;
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;
	};

}