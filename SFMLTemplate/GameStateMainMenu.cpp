#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace ArkanoidGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
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

		setTextParameters(data.menu.rootItem.hintText, L"Змейка", 48, sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.difficultyItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.recordsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParameters(data.startGameItem.text, L"Начать игру", 24);
		setTextParameters(data.difficultyItem.text, L"Уровень сложности", 24);
		setTextParameters(data.optionsItem.text, L"Настройки", 24);
		setTextParameters(data.recordsItem.text, L"Таблица рекордов", 24);

		setTextParameters(data.difficultyItem.hintText, L"Выберите уровень сложности", 48, sf::Color::Red);
		data.difficultyItem.childrenOrientation = Orientation::Vertical;
		data.difficultyItem.childrenAlignment = Alignment::Middle;
		data.difficultyItem.childrenSpacing = 10.f;
		data.difficultyItem.children.push_back(&data.difficultyEasyItem);
		data.difficultyItem.children.push_back(&data.difficultyNormalItem);
		data.difficultyItem.children.push_back(&data.difficultyHardItem);
		data.difficultyItem.children.push_back(&data.difficultyInsaneItem);
		data.difficultyItem.children.push_back(&data.difficultyImpossibleItem);
		setTextParameters(data.difficultyEasyItem.text, L"Лёгкий: вкл/выкл", 24);
		setTextParameters(data.difficultyNormalItem.text, L"Нормальный: On/Off", 24);
		setTextParameters(data.difficultyHardItem.text, L"Сложный: On/Off", 24);
		setTextParameters(data.difficultyInsaneItem.text, L"Безумный: On/Off", 24);
		setTextParameters(data.difficultyImpossibleItem.text, L"Невозможный: On/Off", 24);

		setTextParameters(data.optionsItem.hintText, L"Настройки", 48, sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsSoundItem);
		data.optionsItem.children.push_back(&data.optionsMusicItem);

		setTextParameters(data.optionsSoundItem.text, L"Infinite Apples: On/Off", 24);
		setTextParameters(data.optionsMusicItem.text, L"With Acceleration: On/Off", 24);
		setTextParameters(data.exitGameItem.text, L"Выйти из игры", 24);

		setTextParameters(data.exitGameItem.hintText, L"Вы уверены?", 48, sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		setTextParameters(data.yesItem.text, L"Да", 24);
		setTextParameters(data.noItem.text, L"Нет", 24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::Sound)
				{
					data.soundBtnHover.play();
				}

				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.difficultyItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.difficultyEasyItem)
				{
					game.difficulty = DifficultyLevel::Easy;
				}
				else if (data.menu.selectedItem == &data.difficultyNormalItem)
				{
					game.difficulty = DifficultyLevel::Normal;
				}
				else if (data.menu.selectedItem == &data.difficultyHardItem)
				{
					game.difficulty = DifficultyLevel::Hard;
				}
				else if (data.menu.selectedItem == &data.difficultyInsaneItem)
				{
					game.difficulty = DifficultyLevel::Insane;
				}
				else if (data.menu.selectedItem == &data.difficultyImpossibleItem)
				{
					game.difficulty = DifficultyLevel::Impossible;
				}
				else if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsSoundItem)
				{
					game.options = (GameModeOption)((std::uint8_t)game.options ^ (std::uint8_t)GameModeOption::Sound);
				}
				else if (data.menu.selectedItem == &data.optionsMusicItem)
				{
					game.options = (GameModeOption)((std::uint8_t)game.options ^ (std::uint8_t)GameModeOption::Music);
				}
				else if (data.menu.selectedItem == &data.recordsItem)
				{
					PushGameState(game, GameStateType::Records, true);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		data.difficultyEasyItem.text.setString(L"Лёгкий: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"Вкл" : L"Выкл"));
		data.difficultyNormalItem.text.setString(L"Нормальный: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"Вкл" : L"Выкл"));
		data.difficultyHardItem.text.setString(L"Сложный: " + std::wstring(game.difficulty == DifficultyLevel::Hard ? L"Вкл" : L"Выкл"));
		data.difficultyInsaneItem.text.setString(L"Безумный: " + std::wstring(game.difficulty == DifficultyLevel::Insane ? L"Вкл" : L"Выкл"));
		data.difficultyImpossibleItem.text.setString(L"Невозможный: " + std::wstring(game.difficulty == DifficultyLevel::Impossible ? L"Вкл" : L"Выкл"));

		bool isSound = ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::Sound);
		data.optionsSoundItem.text.setString(L"Звук: " + std::wstring(isSound ? L"Вкл" : L"Выкл"));

		bool isMusic = ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::Music);
		data.optionsMusicItem.text.setString(L"Музыка: " + std::wstring(isMusic ? L"Вкл" : L"Выкл"));
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}