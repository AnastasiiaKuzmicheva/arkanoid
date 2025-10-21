#include "GameStateMainMenu.h"
#include "Application.h"
#include "Application.h"
#include <assert.h>

namespace ArkanoidGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		assert(data.soundBtnHoverBuffer.loadFromFile(SOUNDS_PATH + "\\menu-hover.wav"));

		data.soundBtnHover.setBuffer(data.soundBtnHoverBuffer);

		auto setTextParameters = [&data](sf::Text& itemText, const std::wstring& title, int fontSize, sf::Color color = sf::Color::Transparent)
			{
				itemText.setString(title);
				itemText.setFont(data.font);
				itemText.setCharacterSize(fontSize);
				if (color != sf::Color::Transparent)
				{
					itemText.setFillColor(color);
				}
			};

		Game& game = Application::Instance().GetGame();
		MenuItem startGame;
		setTextParameters(startGame.text, L"Start Game", 24);
		startGame.onPressCallback = [](MenuItem&)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::Playing);
			};

		//MenuItem difficultyEasy;
		setTextParameters(data.difficultyEasy.text, L"Easy: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"On" : L"Off"), 24);
		data.difficultyEasy.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Easy;
				item.text.setString(L"Easy: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"On" : L"Off"));

			};

		//MenuItem difficultyNormal;
		setTextParameters(data.difficultyNormal.text, L"Normal: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"On" : L"Off"), 24);
		data.difficultyNormal.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Normal;
				item.text.setString(L"Normal: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"On" : L"Off"));
			};

		//MenuItem difficultyHard;
		setTextParameters(data.difficultyHard.text, L"Hard: " + std::wstring(game.difficulty == DifficultyLevel::Hard ? L"On" : L"Off"), 24);
		data.difficultyHard.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Hard;
				item.text.setString(L"Hard: " + std::wstring(game.difficulty == DifficultyLevel::Hard ? L"On" : L"Off"));
			};

		//MenuItem difficultyInsane;
		setTextParameters(data.difficultyInsane.text, L"Insane: " + std::wstring(game.difficulty == DifficultyLevel::Insane ? L"On" : L"Off"), 24);
		data.difficultyInsane.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Insane;
				item.text.setString(L"Insane: " + std::wstring(game.difficulty == DifficultyLevel::Insane ? L"On" : L"Off"));
			};

		//MenuItem difficultyImpossible;
		setTextParameters(data.difficultyImpossible.text, L"Impossible: " + std::wstring(game.difficulty == DifficultyLevel::Impossible ? L"On" : L"Off"), 24);
		data.difficultyImpossible.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Impossible;
				item.text.setString(L"Impossible: " + std::wstring(game.difficulty == DifficultyLevel::Impossible ? L"On" : L"Off"));
			};

		MenuItem difficulty;
		setTextParameters(difficulty.text, L"Difficulty level", 24);
		setTextParameters(difficulty.hintText, L"Choose a difficulty level", 48, sf::Color::Red);
		difficulty.childrenOrientation = Orientation::Vertical;
		difficulty.childrenAlignment = Alignment::Middle;
		difficulty.childrenSpacing = 10.f;
		difficulty.childrens.push_back(data.difficultyEasy);
		difficulty.childrens.push_back(data.difficultyNormal);
		difficulty.childrens.push_back(data.difficultyHard);
		difficulty.childrens.push_back(data.difficultyInsane);
		difficulty.childrens.push_back(data.difficultyImpossible);

		bool isSound = IsEnableOptions(Application::Instance().GetGame(), GameOptions::Sound);
		MenuItem optionsSound;
		setTextParameters(optionsSound.text, L"Sound: " + std::wstring(isSound ? L"On" : L"Off"), 24);
		optionsSound.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Sound);
				bool isSound = IsEnableOptions(game, GameOptions::Sound);
				item.text.setString(L"Sound: " + std::wstring(isSound ? L"On" : L"Off"));
			};

		bool isMusic = IsEnableOptions(Application::Instance().GetGame(), GameOptions::Music);
		MenuItem optionsMusic;
		setTextParameters(optionsMusic.text, L"Music: " + std::wstring(isMusic ? L"On" : L"Off"), 24);
		optionsMusic.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Music);
				bool isMusic = IsEnableOptions(game, GameOptions::Music);
				item.text.setString(L"Music: " + std::wstring(isMusic ? L"On" : L"Off"));
			};

		MenuItem options;
		setTextParameters(options.text, L"Options", 24);
		setTextParameters(options.hintText, L"Options", 48, sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;

		options.childrens.push_back(optionsSound);
		options.childrens.push_back(optionsMusic);

		MenuItem records;
		setTextParameters(records.text, L"Leaderboard", 24);
		records.onPressCallback = [](MenuItem&)
			{
				PushGameState(Application::Instance().GetGame(), GameStateType::Records, true);
			};

		MenuItem yesItem;
		setTextParameters(yesItem.text, L"Yes", 24);
		yesItem.onPressCallback = [](MenuItem&)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::None);
			};

		MenuItem noItem;
		setTextParameters(noItem.text, L"No", 24);
		noItem.onPressCallback = [&data](MenuItem&)
			{
				data.menu.GoBack();
			};

		MenuItem exitGame;
		setTextParameters(exitGame.text, L"Quit game", 24);

		setTextParameters(exitGame.hintText, L"Quit game?", 48, sf::Color::Red);
		exitGame.childrenOrientation = Orientation::Horizontal;
		exitGame.childrenAlignment = Alignment::Middle;
		exitGame.childrenSpacing = 10.f;
		exitGame.childrens.push_back(yesItem);
		exitGame.childrens.push_back(noItem);

		MenuItem mainMenu;
		setTextParameters(mainMenu.hintText, L"Arkanoid", 48, sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(difficulty);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(records);
		mainMenu.childrens.push_back(exitGame);

		data.menu.Init(mainMenu);

		
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				data.menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (IsEnableOptions(game, GameOptions::Sound))
				{
					data.soundBtnHover.play();
				}

				data.menu.PressOnSelectedItem();
			}

			Orientation orientation = data.menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				data.menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				data.menu.SwitchToNextMenuItem();
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta)
	{
		Game& game = Application::Instance().GetGame();
		data.difficultyEasy.text.setString(L"Easy: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"On" : L"Off"));
		data.difficultyNormal.text.setString(L"Normal: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"On" : L"Off"));
		data.difficultyHard.text.setString(L"Hard: " + std::wstring(game.difficulty != DifficultyLevel::Hard ? L"On" : L"Off"));
		data.difficultyInsane.text.setString(L"Insane: " + std::wstring(game.difficulty != DifficultyLevel::Insane ? L"On" : L"Off"));
		data.difficultyImpossible.text.setString(L"Impossible: " + std::wstring(game.difficulty != DifficultyLevel::Impossible ? L"On" : L"Off"));

	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &data.menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		data.menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}