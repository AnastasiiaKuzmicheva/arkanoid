#include "GameStateExitDialog.h"
#include "Application.h"
#include <assert.h>
#include "Math.h"

namespace ArkanoidGame
{
	void GameStateExitDialogData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		hintText.setString(L"Âû óâåðåíû ÷òî õîòèòå çàâåðøèòü ýòó èãðó? Enter - Äà, Esc - Íåò");
		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 0.5f }));

		background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
	}

	void GameStateExitDialogData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
			}
		}
	}

	void GameStateExitDialogData::Update(float deltaTime)
	{

	}

	void GameStateExitDialogData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

		background.setSize(windowSize);
		window.draw(background);

		hintText.setPosition(windowSize / 2.f);
		window.draw(hintText);
	}
}