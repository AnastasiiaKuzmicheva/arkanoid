#include <assert.h>
#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"

namespace ArkanoidGame
{
	void GameStateMainMenuData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(soundBtnHoverBuffer.loadFromFile(SOUNDS_PATH + "\\menu-hover.wav"));

		soundBtnHover.setBuffer(soundBtnHoverBuffer);

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [](MenuItem&) 
		{
			Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
		};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(font);
		options.text.setCharacterSize(24);
		options.hintText.setString("Options");
		options.hintText.setFont(font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;

		
		MenuItem recordsItem;
		recordsItem.text.setString("Leaderboard");
		recordsItem.text.setFont(font);
		recordsItem.text.setCharacterSize(24);
		recordsItem.onPressCallback = [](MenuItem&)
		{
				Application::Instance().GetGame().PushState(GameStateType::Records, true);
		};


		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&)
		{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::None);
		};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [this](MenuItem&)
		{
				menu.GoBack();
		};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Quit game");
		exitGameItem.text.setFont(font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenuItem;
		mainMenuItem.hintText.setString("Arkanoid");
		mainMenuItem.hintText.setFont(font);
		mainMenuItem.hintText.setCharacterSize(48);
		mainMenuItem.hintText.setFillColor(sf::Color::Red);
		mainMenuItem.childrenOrientation = Orientation::Vertical;
		mainMenuItem.childrenAlignment = Alignment::Middle;
		mainMenuItem.childrenSpacing = 10.f;
		mainMenuItem.childrens.push_back(startGame);
		mainMenuItem.childrens.push_back(options);
		mainMenuItem.childrens.push_back(recordsItem);
		mainMenuItem.childrens.push_back(exitGameItem);

		menu.Init(mainMenuItem);

		
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