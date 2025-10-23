#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		//Resources
	
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer soundAppleEatBuffer;
		sf::SoundBuffer soundDeathBuffer;
		sf::SoundBuffer soundBackgroundBuffer;

		sf::Font font;

		Platform platform;
		Ball ball;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		//Sound
		sf::Sound soundDeath;
		sf::Sound soundBackground;
	};

}
