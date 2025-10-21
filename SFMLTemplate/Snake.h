#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <list>
#include <array>

namespace ArkanoidGame
{
	enum class SnakeDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	enum class SnakePart : uint8_t
	{
		Head = 0,
		Body,
		BodyBend,
		Tail,
		Count
	};

	struct Snake
	{
		std::list<sf::Sprite> body;
		std::list<sf::Sprite>::iterator head;
		std::list<sf::Sprite>::iterator tail;

		//Position2D position;
		float speed = INITIAL_SPEED;
		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;
		//sf::Sprite sprite;

		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};

	//struct Game;
	//struct GameStatePlayingData;

	void LoadSnakeTextures(Snake& snake);

	void InitPlayer(Snake& snake);
	void GrowSnake(Snake& snake);
	void DrawPlayer(Snake& snake, sf::RenderWindow& window);

	void HandleInput(Snake& snake);
	void UpdateInput(Snake& snake, float deltaTime);

	bool HasSnakeCollisionWithRect(const Snake& snake, const sf::FloatRect& rect);
	bool CheckSnakeCollisionWithHimself(Snake& snake);
	bool CheckSnakeCollisionWithSprite(Snake& snake, const sf::Sprite& sprite);

	sf::Vector2f GetDirectionVector(SnakeDirection direction);
}
