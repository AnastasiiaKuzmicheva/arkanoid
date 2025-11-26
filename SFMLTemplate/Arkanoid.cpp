// Arkanoid.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "Application.h"

using namespace ArkanoidGame;

int main()
{
	Application::Instance().Run();

	return 0;
}