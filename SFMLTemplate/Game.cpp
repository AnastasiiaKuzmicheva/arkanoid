#include <cassert>
#include <algorithm>
#include "Game.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameRecords.h"


namespace ArkanoidGame
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"John", rand() % 10},
			{"Jane", rand() % 10 },
			{"Alice", rand() % 10 },
			{"Bob", rand() % 10 },
			{"Clementine", rand() % 10 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingStateType = GameStateType::None;
		pendingStateIsExclusivelyVisible = false;

		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().HandleWindowEvent(event);
			}
		}
	}

	bool Game::Update (float deltaTime)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingStateType != GameStateType::None)
		{
			stateStack.push_back(GameState(pendingStateType,
		pendingStateIsExclusivelyVisible));
			
		}

		stateChangeType = GameStateChangeType::None;
		pendingStateType = GameStateType::None;
		pendingStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().Update(deltaTime);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;

			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (stateStack.size() > 0)
		{
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingStateType = GameStateType::None;
		pendingStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingStateType = stateType;
		pendingStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingStateType = GameStateType::None;
		pendingStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingStateType = newState;
		pendingStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	
	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else
		{
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}
}

