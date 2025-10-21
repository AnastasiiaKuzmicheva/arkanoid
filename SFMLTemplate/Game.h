#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Sprite.h"
#include "Snake.h"
#include "Apple.h"
#include "Rock.h"
#include <iostream>
#include <unordered_map>

namespace ArkanoidGame
{
	enum class GameModeOption : std::uint8_t
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

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameModeOption options = GameModeOption::Default;
		DifficultyLevel difficulty = DifficultyLevel::Normal;

		std::unordered_map<std::string, int> recordsTable;

	};

	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float timeDelta);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}

