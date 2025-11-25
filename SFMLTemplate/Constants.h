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

	const float ACCELERATION = 10.f;
	const int MAX_APPLES = 80;

	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

	const unsigned int BALL_SIZE = 30;
	const unsigned int BALL_SPEED = 200;

	const unsigned int PLATFORM_WIDTH = 60;
	const unsigned int PLATFORM_HEIGHT = 20;
	const float PLATFORM_SPEED = 300.f;

	const unsigned int BLOCKS_COUNT_ROWS = 2;
	const unsigned int BLOCKS_COUNT_IN_ROW = 10;
	const unsigned int BLOCK_SHIFT = 5;
	const unsigned int BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_COUNT_IN_ROW + 1) * BLOCK_SHIFT) / BLOCKS_COUNT_IN_ROW;
	const unsigned int BLOCK_HEIGHT = 20;

	const unsigned int START_Y = 50;  // Отступ сверху
	const unsigned int ROW_HEIGHT = BLOCK_HEIGHT + BLOCK_SHIFT;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some SPP

	const std::string GAME_NAME = "ArkanoidGame";

}
