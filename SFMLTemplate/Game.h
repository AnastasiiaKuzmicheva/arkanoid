#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameState.h"
#include <unordered_map>

namespace ArkanoidGame
{
	enum class GameOptions : std::uint8_t
	{
		Sound = 1 << 0,
		Music = 1 << 1,

		Default = Sound | Music,
		Empty = 0
	};

	enum class DifficultyLevel : std::uint8_t
	{
		Easy,
		Normal,
		Hard,
		Insane,
		Impossible,
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
		bool Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		void SetOption(GameOptions option, bool value);
		void SetDifficultyLevel(DifficultyLevel level, bool value);
		bool IsEnableOptions(GameOptions option);
		bool IsEnableDifficultyLevel(DifficultyLevel level);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		// Add new game state on top of the stack
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
		DifficultyLevel difficulty = DifficultyLevel::Normal;

		RecordsTable recordsTable;
	};
}