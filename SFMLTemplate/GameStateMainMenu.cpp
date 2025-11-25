#include "GameStateMainMenu.h"
#include "Application.h"
#include <assert.h>

namespace ArkanoidGame
{
	void GameStateMainMenuData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		assert(soundBtnHoverBuffer.loadFromFile(SOUNDS_PATH + "\\menu-hover.wav"));

		soundBtnHover.setBuffer(soundBtnHoverBuffer);

		auto setTextParameters = [&](sf::Text& itemText, const std::wstring& title, int fontSize, sf::Color color = sf::Color::Transparent)
			{
				itemText.setString(title);
				itemText.setFont(font);
				itemText.setCharacterSize(fontSize);
				if (color != sf::Color::Transparent)
				{
					itemText.setFillColor(color);
				}
			};

		Game& game = Application::Instance().GetGame();
		MenuItem startGame;
		setTextParameters(startGame.text, L"Íà÷àòü èãðó", 24);
		startGame.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			};

		const bool isEasy = game.IsEnableDifficultyLevel(DifficultyLevel::Easy);
		MenuItem difficultyEasy;
		setTextParameters(difficultyEasy.text, L"Ë¸ãêèé: " + std::wstring(isEasy ? L"Âêë" : L"Âûêë"), 24);
		difficultyEasy.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newEasy = !game.IsEnableDifficultyLevel(DifficultyLevel::Easy);
				game.SetDifficultyLevel(DifficultyLevel::Easy, newEasy);
				item.text.setString(L"Ë¸ãêèé: " + std::wstring(newEasy ? L"Âêë" : L"Âûêë"));
			};

		const bool isNormal = game.IsEnableDifficultyLevel(DifficultyLevel::Normal);
		MenuItem difficultyNormal;
		setTextParameters(difficultyNormal.text, L"Íîðìàëüíûé: " + std::wstring(isNormal ? L"Âêë" : L"Âûêë"), 24);
		difficultyNormal.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newNormal = !game.IsEnableDifficultyLevel(DifficultyLevel::Normal);
				game.SetDifficultyLevel(DifficultyLevel::Normal, newNormal);
				item.text.setString(L"Íîðìàëüíûé: " + std::wstring(newNormal ? L"Âêë" : L"Âûêë"));
			};

		const bool isHard = game.IsEnableDifficultyLevel(DifficultyLevel::Hard);
		MenuItem difficultyHard;
		setTextParameters(difficultyHard.text, L"Ñëîæíûé: " + std::wstring(isHard ? L"Âêë" : L"Âûêë"), 24);
		difficultyHard.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newHard = !game.IsEnableDifficultyLevel(DifficultyLevel::Hard);
				game.SetDifficultyLevel(DifficultyLevel::Hard, newHard);
				item.text.setString(L"Ñëîæíûé: " + std::wstring(newHard ? L"Âêë" : L"Âûêë"));
			};

		const bool isInsane = game.IsEnableDifficultyLevel(DifficultyLevel::Insane);
		MenuItem difficultyInsane;
		setTextParameters(difficultyInsane.text, L"Áåçóìíûé: " + std::wstring(isInsane ? L"Âêë" : L"Âûêë"), 24);
		difficultyInsane.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newInsane = !game.IsEnableDifficultyLevel(DifficultyLevel::Insane);
				game.SetDifficultyLevel(DifficultyLevel::Insane, newInsane);
				item.text.setString(L"Áåçóìíûé: " + std::wstring(newInsane ? L"Âêë" : L"Âûêë"));
			};

		const bool isImpossible = game.IsEnableDifficultyLevel(DifficultyLevel::Impossible);
		MenuItem difficultyImpossible;
		setTextParameters(difficultyImpossible.text, L"Íåâîçìîæíûé: " + std::wstring(isImpossible ? L"Âêë" : L"Âûêë"), 24);
		difficultyImpossible.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newImpossible = !game.IsEnableDifficultyLevel(DifficultyLevel::Impossible);
				game.SetDifficultyLevel(DifficultyLevel::Impossible, newImpossible);
				item.text.setString(L"Íåâîçìîæíûé: " + std::wstring(newImpossible ? L"Âêë" : L"Âûêë"));
			};

		MenuItem difficulty;
		setTextParameters(difficulty.text, L"Óðîâåíü ñëîæíîñòè", 24);
		setTextParameters(difficulty.hintText, L"Âûáåðèòå óðîâåíü ñëîæíîñòè", 48, sf::Color::Red);
		difficulty.childrenOrientation = Orientation::Vertical;
		difficulty.childrenAlignment = Alignment::Middle;
		difficulty.childrenSpacing = 10.f;
		difficulty.children.push_back(difficultyEasy);
		difficulty.children.push_back(difficultyNormal);
		difficulty.children.push_back(difficultyHard);
		difficulty.children.push_back(difficultyInsane);
		difficulty.children.push_back(difficultyImpossible);


		const bool isSound = game.IsEnableOptions(GameOptions::Sound);

		MenuItem optionsSound;
		setTextParameters(optionsSound.text, L"Çâóê: " + std::wstring(isSound ? L"Âêë" : L"Âûêë"), 24);
		optionsSound.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newSound = !game.IsEnableOptions(GameOptions::Sound);
				game.SetOption(GameOptions::Sound, newSound);
				item.text.setString(L"Çâóê: " + std::wstring(newSound ? L"Âêë" : L"Âûêë"));
			};

		const bool isMusic = game.IsEnableOptions(GameOptions::Music);
		MenuItem optionsMusic;
		setTextParameters(optionsMusic.text, L"Ìóçûêà: " + std::wstring(isMusic ? L"Âêë" : L"Âûêë"), 24);
		optionsMusic.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newMusic = !game.IsEnableOptions(GameOptions::Music);
				game.SetOption(GameOptions::Music, newMusic);
				item.text.setString(L"Ìóçûêà: " + std::wstring(newMusic ? L"Âêë" : L"Âûêë"));
			};

		MenuItem options;
		setTextParameters(options.text, L"Íàñòðîéêè", 24);
		setTextParameters(options.hintText, L"Íàñòðîéêè", 48, sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;

		options.children.push_back(optionsSound);
		options.children.push_back(optionsMusic);


		MenuItem records;
		setTextParameters(records.text, L"Òàáëèöà ðåêîðäîâ", 24);
		records.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().PushState(GameStateType::Records, true);
			};

		MenuItem yesItem;
		setTextParameters(yesItem.text, L"Äà", 24);
		yesItem.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::None);
			};

		MenuItem noItem;
		setTextParameters(noItem.text, L"Íåò", 24);
		noItem.onPressCallback = [&](MenuItem&)
			{
				menu.GoBack();
			};

		MenuItem exitGame;
		setTextParameters(exitGame.text, L"Âûéòè èç èãðû", 24);

		setTextParameters(exitGame.hintText, L"Âû óâåðåíû?", 48, sf::Color::Red);
		exitGame.childrenOrientation = Orientation::Horizontal;
		exitGame.childrenAlignment = Alignment::Middle;
		exitGame.childrenSpacing = 10.f;
		exitGame.children.push_back(yesItem);
		exitGame.children.push_back(noItem);

		MenuItem mainMenu;
		setTextParameters(mainMenu.hintText, L"Arcanoid", 48, sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.children.push_back(startGame);
		mainMenu.children.push_back(difficulty);
		mainMenu.children.push_back(options);
		mainMenu.children.push_back(records);
		mainMenu.children.push_back(exitGame);

		menu.Init(mainMenu);
	}

	void GameStateMainMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (Application::Instance().GetGame().IsEnableOptions(GameOptions::Sound))
				{
					soundBtnHover.play();
				}

				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::Update(float deltaTime)
	{

	}

	void GameStateMainMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}