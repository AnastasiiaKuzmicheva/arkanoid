#include "BlockFactory.h"
#include "Block.h"

namespace ArkanoidGame
{
	int BlockFactory::GetCreatedBreackableBlocksCount() {

		return createdBreackableBlocksCount;
	}

	void BlockFactory::ClearCounter()
	{
		createdBreackableBlocksCount = 0;
	}

	std::shared_ptr<Block> SimpleBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<SmoothDestroyableBlock>(position);
	}

	std::shared_ptr<Block> GlassBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		return std::make_shared<GlassBlock>(position);
	}

	std::shared_ptr<Block> ThreeHitBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<ThreeHitBlock>(position);
	}
}