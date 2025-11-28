#include "GameBonus.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include "Ball.h"
#include "Platform.h"
#include "Application.h"

namespace
{
	// id textures
	const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{
	// Ýôôåêòû
	class ExpandPlatformEffect : public IBonusEffect
	{
	public:
		void Apply(Platform& platform, Ball&) override { platform.SetWidth(1.5f); }
		void Revert(Platform& platform, Ball&) override { platform.SetWidth(1.0f); }
	};

	class SlowBallEffect : public IBonusEffect
	{
	public:
		void Apply(Platform&, Ball& ball) override { ball.SetMultiplySpeed(0.5f); }
		void Revert(Platform&, Ball& ball) override { ball.SetMultiplySpeed(1.0f); }
	};

	static std::unique_ptr<IBonusEffect> CreateEffect(BonusType type) {
		switch (type) {
		case BonusType::ExpandPlatform: return std::make_unique<ExpandPlatformEffect>();
			//case BonusType::ExtraLife: return std::make_unique<ExtraLifeEffect>();
			//case BonusType::MultiBall: return std::make_unique<MultiBallEffect>();
		case BonusType::SlowBall: return std::make_unique<SlowBallEffect>();
		default: return nullptr;
		}
	}

	GameBonus::GameBonus(const sf::Vector2f& position, BonusType type)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, static_cast<float>(SETTINGS.BONUS_SIZE), static_cast<float>(SETTINGS.BONUS_SIZE)), type(type), effect(CreateEffect(type))
	{
		duration = 5.f + static_cast<float>(rand() % 6);;
	}

	void GameBonus::Update(float deltaTime)
	{
		sprite.move(0.f, 100.f * deltaTime);

		if (effectApplied)
		{
			timer += deltaTime;
			if (timer >= duration)
			{
				active = false;
			}
		}
	}

	void GameBonus::OnCollect(Platform& platform, Ball& ball)
	{
		if (!effectApplied && effect)
		{
			effect->Apply(platform, ball);
			effectApplied = true;
			timer = 0.f;
		}
	}

	void GameBonus::OnEffectEnd(Platform& platform, Ball& ball)
	{
		if (effectApplied && effect)
		{
			effect->Revert(platform, ball);
			effectApplied = false;
		}
	}
}