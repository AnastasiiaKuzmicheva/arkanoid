#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStateData.h"
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	
	class Game;

	class GameStatePlayingData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		//Resources
	
		sf::SoundBuffer soundDeathBuffer;
		sf::SoundBuffer soundBackgroundBuffer;

		sf::Font font;

		std::vector<std::shared_ptr<GameObject>> gameObjects;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		//Sound
		sf::Sound soundDeath;
		sf::Sound soundBackground;
	};

}
