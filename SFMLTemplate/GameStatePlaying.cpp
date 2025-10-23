#include <sstream>
#include <assert.h>
#include "GameStatePlaying.h"
#include "Application.h"
#include "Text.h"
#include "Game.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
	
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(soundDeathBuffer.loadFromFile(SOUNDS_PATH + "\\GameOver.wav"));
		assert(soundBackgroundBuffer.loadFromFile(SOUNDS_PATH + "\\Background.wav"));


		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(16);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString(L"Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		platform.Init();
		ball.Init();

		soundBackground.setBuffer(soundBackgroundBuffer);

		soundDeath.setBuffer(soundDeathBuffer);
				
	}

	
	void  GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float deltaTime)
	{
		platform.Update(deltaTime);
		ball.Update(deltaTime);

		const bool isCollision = platform.CheckCollisionWithBall(ball);
		if (isCollision)
		{
			ball.ReboundFromPlatform();
		}

		const bool isGameFinished = !isCollision && ball.GetPosition().y > platform.GetRect().top;
		
		if (isGameFinished)
		{
			soundDeath.play();

			Game& game = Application::Instance().GetGame();
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		platform.Draw(window);
		ball.Draw(window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}