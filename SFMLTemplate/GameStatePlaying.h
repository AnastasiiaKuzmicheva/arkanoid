#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Apple.h"
#include "Rock.h"
#include "Snake.h"

namespace ArkanoidGame
{
	struct Game;

	struct GameStatePlayingData
	{
		//Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer soundAppleEatBuffer;
		sf::SoundBuffer soundDeathBuffer;
		sf::SoundBuffer soundBackgroundBuffer;

		sf::Font font;

		//Game data
		Snake snake;
		Apple apple;
		Rock rocks[NUM_ROCKS];
		std::vector<Apple> apples;
		int numApple = 5;
		int numEatenApples = 0;
		bool isGameFinished = false;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		//Sound
		sf::Sound soundAppleEat;
		sf::Sound soundDeath;
		sf::Sound soundBackground;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);

	void DifficultyLevelState(GameStatePlayingData& data, Game& game);
}
