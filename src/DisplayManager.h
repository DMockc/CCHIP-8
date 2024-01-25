#pragma once
#include "../include/SDL.h"
#include "../include/SDL_ttf.h"
#include <vector>
#include <iostream>

#define WHITE	255, 255, 255, 255
#define BLACK	0, 0, 0, 255
#define HEIGHT	32
#define WIDTH	64
#define FILL_HEIGHT 20
#define FILL_WIDTH 14

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
	
	void clearDisplay();
	void drawMatrix(int offset);
	void writeText(const char* text);
	void fillTextPlace(int offset);

	SDL_Renderer* renderer;

	bool screenMatrix[HEIGHT][WIDTH];
	Uint8 text_alpha;
	std::vector<DRW_COORD> coords_buffer;

private:
	void loadFont();

	SDL_Window* m_window;
	TTF_Font* m_font;
	SDL_Surface* m_text;
	SDL_Rect textBox;
};