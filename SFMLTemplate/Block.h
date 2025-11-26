#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "Collision.h"
#include "DelayedAction.h"


namespace ArkanoidGame
{
	class Block : public GameObject, public Collision
	{
	public:

		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();
		bool GetCollision(std::shared_ptr<Collision> collisionObject) const override;
		void Update(float timeDelta) override;
		bool IsBroken();

	protected:

		void OnHit() override;
		int hitCount = 1;
	};

	class SmoothDestroyableBlock : public Block, public DelayedAction
	{
	public:

		SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		~SmoothDestroyableBlock() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Collision> collisionObject) const override;

	protected:

		void OnHit() override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
		sf::Color color;
	};

	class UnbreackableBlock : public Block
	{
	public:

		UnbreackableBlock(const sf::Vector2f& position);
		void OnHit() override;
		void Update(float)
		{
			int i = 0;
			++i;
		};
	};
}