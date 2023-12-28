#pragma once
#include "../include/SDL.h"
#include <vector>
#include <iostream>

#define WHITE	255, 255, 255, 255
#define BLACK	0, 0, 0, 255

using uByte = unsigned char;

/*
*	DRW_COORD is a structure that stores the pixel 
*	coordinates and the state (black or white).
*/
struct DRW_COORD
{
	DRW_COORD(uByte x, uByte y, bool color);

	uByte x_coord;
	uByte y_coord;
	SDL_Color pixel_color;
};

class DisplayManager
{
public:
	DisplayManager();
	~DisplayManager();
	
	void drawMatrix(int offset);

	SDL_Renderer* renderer;

	const int HEIGHT = 32;
	const int WIDTH = 64;
	bool screenMatrix[32][64];

	std::vector<DRW_COORD> coords_buffer;

private:
	SDL_Window* m_window;
};