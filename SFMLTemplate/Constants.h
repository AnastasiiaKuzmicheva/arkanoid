#pragma once
#include <string>

namespace ArkanoidGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const float INITIAL_SPEED = 50.0f; //Pixels per second
	const int MAX_APPLES = 80;

	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some SPP

	const std::string GAME_NAME = "ArkanoidGame";

}
