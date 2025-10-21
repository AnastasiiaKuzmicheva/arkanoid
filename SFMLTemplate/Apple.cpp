
#include "Apple.h"
#include "Game.h"
#include <iostream>

namespace ArkanoidGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);

		//Init apple sprite
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);


	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.position.X, apple.position.Y);
		window.draw(apple.sprite);
	}
}