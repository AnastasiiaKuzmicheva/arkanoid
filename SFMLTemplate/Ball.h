#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collision.h"

namespace ArkanoidGame
{
	class Ball : public GameObject, public Collision
	{
	public:

		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float deltaTime) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<Collision> collision) const  override;
		void ChangeAngle(float x);

	private:

		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}