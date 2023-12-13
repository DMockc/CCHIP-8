#pragma once
#include "../include/SDL.h"
#include <vector>
#include <iostream>

#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 255

using uByte = unsigned char;

struct DRW_COORD
{
	DRW_COORD(uByte x, uByte y, bool c);

	uByte x_coord;
	uByte y_coord;
	SDL_Color color;
};

class DisplayManager
{
public:
	DisplayManager();
	~DisplayManager();
	
	void drawMatrix(int offset);

	SDL_Renderer* renderer;

	const int HEIGHT = 256; //32 * 8
	const int WIDTH = 512; //64 * 8
	bool** screenMatrix;

	std::vector<DRW_COORD> coords_buffer;

private:
	SDL_Window* m_window;
};