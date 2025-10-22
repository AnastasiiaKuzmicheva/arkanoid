#include "GameStatePlaying.h"
#include "Application.h"
#include "assert.h"
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		snake.LoadTextures();

		assert(appleTexture.loadFromFile(TEXTURES_PATH + "\\apple.png"));
		assert(rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(soundAppleEatBuffer.loadFromFile(SOUNDS_PATH + "\\AppleEat.wav"));
		assert(soundDeathBuffer.loadFromFile(SOUNDS_PATH + "\\GameOver.wav"));
		assert(soundBackgroundBuffer.loadFromFile(SOUNDS_PATH + "\\Background.wav"));


		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		snake.Init();

		InitSprite(apple, APPLE_SIZE, APPLE_SIZE, appleTexture);
		SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.GetBody());

		rocks.resize(NUM_ROCKS);
		for (sf::Sprite& rock : rocks)
		{
			InitSprite(rock, ROCK_SIZE, ROCK_SIZE, rockTexture);
			SetSpriteRandomPosition(rock, background.getGlobalBounds(), snake.GetBody());
		}

		numEatenApples = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(16);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString(L"Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		soundBackground.setBuffer(soundBackgroundBuffer);

		soundAppleEat.setBuffer(soundAppleEatBuffer);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			snake.SetDirection(SnakeDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			snake.SetDirection(SnakeDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			snake.SetDirection(SnakeDirection::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			snake.SetDirection(SnakeDirection::Left);
		}

		// Update snake
		snake.Move(deltaTime);
		
		if (CheckSpriteIntersection(*snake.GetHead(), apple)) 
		{
			soundAppleEat.play();
			snake.Grow();
			numEatenApples++;
			SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.GetBody());
			// Increase snake speed
			if (Application::Instance().GetGame().IsEnableOptions(GameOptions::WithAcceleration)) 
			{
				snake.SetSpeed(snake.GetSpeed() + ACCELERATION);
			}
		}

		const bool isGameFinished = numEatenApples == MAX_APPLES &&
			!Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);

		if (isGameFinished
			|| !snake.HasCollisionWithRect(background.getGlobalBounds()) // Check collision with screen border
			|| snake.CheckCollisionWithHimself()		// Check collision with screen border
			|| FullCheckCollisions(rocks.begin(), rocks.end(), *snake.GetHead())) // Check collision with rocks
		{
			soundDeath.play();

			Game& game = Application::Instance().GetGame();
			game.UpdateRecord(PLAYER_NAME, numEatenApples);
			game.PushState(GameStateType::GameOver, false);
		}
		scoreText.setString("Apples eaten: " + std::to_string(numEatenApples));
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw snake
		snake.Draw(window);

		DrawSprite(apple, window);

		DrawSprites(rocks.begin(), rocks.end(), window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}