#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Apple.h"
#include "Rock.h"
#include "Snake.h"

namespace ArkanoidGame
{
	
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

	void InitGameStatePlaying(GameStatePlayingData& data);
	void ShutdownGameStatePlaying(GameStatePlayingData& data);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, sf::RenderWindow& window);

	void DifficultyLevelState(GameStatePlayingData& data);
}
