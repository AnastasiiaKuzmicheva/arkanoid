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

	class Snake
	{
	public:
		void Init();
		void LoadTextures();
		void Move(float deltaTime);
		void Grow();
		void Draw(sf::RenderWindow& window);

		bool HasCollisionWithRect(const sf::FloatRect& rect);
		bool CheckCollisionWithHimself();
		bool CheckCollisionWithSprite(const sf::Sprite& sprite);

		void SetDirection(SnakeDirection newDirection) { direction = newDirection; }
		void SetSpeed(float value) { speed = value; }

		std::list<sf::Sprite> GetBody() const { return body; }
		std::list<sf::Sprite>::iterator GetTail() { return body.begin(); }
		std::list<sf::Sprite>::iterator GetHead() { return --body.end(); }
		float GetSpeed() const { return speed; }
		SnakeDirection GetDirection() const { return direction; }

	private:
		sf::Vector2f GetDirectionVector(SnakeDirection direction);
		void UpdateHeadSprite();
		void UpdateTailSprite();
		sf::Sprite GetRotationSprite(SnakeDirection olddirection, SnakeDirection newDirection);
	private:
		std::list<sf::Sprite> body;
		float speed = 0.f; //pixels per second
		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;
		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};
}
