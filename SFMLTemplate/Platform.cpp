#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include "Math.h"

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Platform::Platform(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, PLATFORM_WIDTH, PLATFORM_HEIGHT)
	{
	
	}

	void Platform::Update(float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Move(-deltaTime * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Move(deltaTime * PLATFORM_SPEED);
		}
	}

	void Platform::Move(float speed)
	{
		auto position = sprite.getPosition();
		position.x = clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::GetCollision(std::shared_ptr<Collision> collision) const
	{
		auto ball = std::static_pointer_cast<Ball>(collision);
		if (!ball) return false;

		auto sqr = [](float x)
			{
				return x * x;
			};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->GetPosition();

		if (ballPos.x < rect.left)
		{
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}
	bool Platform::CheckCollision(std::shared_ptr<Collision> collision)
	{
		auto ball = std::static_pointer_cast<Ball>(collision);
		if (!ball)
			return false;

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosInOlatform = (ball->GetPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosInOlatform);
			return true;
		}
		return false;
	}
}