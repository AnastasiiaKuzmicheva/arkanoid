#include "Block.h"
#include "Sprite.h"
#include "GameSettings.h"
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, PLATFORM_WIDTH, PLATFORM_HEIGHT)
	{
		sprite.setColor(color);
	}

	bool Block::GetCollision(std::shared_ptr<Collision> collisionObject) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collisionObject);
		assert(gameObject);
		sf::FloatRect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void Block::Update(float deltaTime)
	{

	}

	Block::~Block()
	{

	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{

	}

	void SmoothDestroyableBlock::Update(float deltaTime)
	{
		UpdateTimer(deltaTime);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Collision> collisionObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collisionObject);
		assert(gameObject);
		sf::FloatRect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(BREAK_DELAY);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		const float alphaDecay = 255.f * (deltaTime / BREAK_DELAY);
		if (color.a > alphaDecay)
		{
			color.a -= static_cast<sf::Uint8>(alphaDecay);
		}
		else
		{
			color.a = 0;
		}
		sprite.setColor(color);
	}

	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Blue)
	{

	}

	void UnbreackableBlock::OnHit()
	{
		// Do nothing
	}
}