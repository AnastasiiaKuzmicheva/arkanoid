#include <cstdlib>
#include "Application.h"

namespace ArkanoidGame
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	Application::Application() :
		window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME)
	{
		//init random number generator
		unsigned int seed = (unsigned int)time(nullptr); //get current time as seed. Yoy can also use any number to fix randomization
		srand(seed);

	}

	void Application::Run()
	{
		//init game clock
		sf::Clock gameClock;

		//Game loop
		while (window.isOpen())
		{
			float startTime = gameClock.getElapsedTime().asSeconds();

			game.HandleWindowEvents(window);

			if (!window.isOpen())
			{
				break;
			}

			if (game.Update(TIME_PER_FRAME))
			{
				//draw everithing here
				//clear the window first
				window.clear();

				game.Draw(window);

				//end the current frame, display window contents on screen
				window.display();
			}
			else
			{
				window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < TIME_PER_FRAME)
			{
				//reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
			}
		}
	}


}