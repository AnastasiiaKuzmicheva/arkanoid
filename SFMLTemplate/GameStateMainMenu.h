#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStateData.h"
#include "Menu.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateMainMenuData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;
		Menu menu;
		sf::SoundBuffer soundBtnHoverBuffer;
		sf::Sound soundBtnHover;
	};
}

