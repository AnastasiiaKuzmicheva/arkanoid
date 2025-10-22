#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Constants.h"
#include "Math.h"
#include "GameState.h"
#include "Sprite.h"
#include "Snake.h"
#include "Apple.h"
#include "Rock.h"

namespace ArkanoidGame
{
	enum class GameOptions : std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	
	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float deltaTime); //return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		//add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopState();

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);

	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingStateType = GameStateType::None;
		bool pendingStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;		

	};

}

