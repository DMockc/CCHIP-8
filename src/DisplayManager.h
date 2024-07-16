#pragma once
#include "../include/SDL.h"
#include "../include/SDL_ttf.h"
#include <vector>
#include <iostream>

#define WHITE	255, 255, 255, 255
#define BLACK	0, 0, 0, 255

#define WIDTH	64
#define HEIGHT	32
#define FILL_WIDTH	14
#define FILL_HEIGHT	8

#define WIN_ARIAL_FONT_DIR "C:\\Windows\\Fonts\\arial.ttf"

/* PIXEL OFFSET */
#define OFFSET	16

using uByte = unsigned char;

/* Display Text */
struct dTEXT
{
	dTEXT(const char* content, int x, int y, SDL_Color color, bool blend);

	std::string t_content; //Text Content
	int x, y;
	bool active;
	bool blend;
	SDL_Color color;
	SDL_Rect textPlace;
};

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

void waitFPS(Uint32 delta, Uint32 desiredDelta);

class DisplayManager
{
public:
	DisplayManager();
	~DisplayManager();
	
	void clearDisplay();
	void drawMatrix();
	void writeText(dTEXT& text);
	void fillTextPlace(dTEXT& text);
	void updateAlpha(dTEXT& text, bool speedup, bool slowdown);
	void updateSpeedText(dTEXT& text);
	void DisplayQuit();

	SDL_Renderer* renderer;

	bool screenMatrix[HEIGHT][WIDTH];
	std::vector<DRW_COORD> coords_buffer;
private:
	void loadFont();
	void clearTextPlace(dTEXT& text);

	SDL_Window* m_window;
	SDL_Surface* m_text;
	TTF_Font* m_font;
};
