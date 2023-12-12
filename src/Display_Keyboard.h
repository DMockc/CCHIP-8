#pragma once

#include "../include/SDL.h"
#include <iostream>
#include <vector>


#define KEYMAP_SIZE 0x10
#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 0


using uByte = unsigned char;
using uWord = unsigned short;

struct DRW_COORD
{
	DRW_COORD(uByte x, uByte y, bool c);

	uByte x_coord;
	uByte y_coord;
	SDL_Color color;
};

namespace DisplayAndKeyboard_Manager
{
	extern bool keymap[KEYMAP_SIZE];
	const int WIDTH = 512; //64 * 8
	const int HEIGHT = 256; //32 * 8
	extern SDL_Renderer* renderer;
	extern SDL_Window* window;
	extern std::vector< DRW_COORD > coords_buffer;
	extern bool screenMatrix[HEIGHT][WIDTH];

	void initDisplay();
	bool isPressed(uByte key);
	void drawMatrix(int offset);
	void endDisplay();
};
