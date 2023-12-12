#include "Display_Keyboard.h"

DRW_COORD::DRW_COORD(uByte x, uByte y, bool c)
	: x_coord(x), y_coord(y)
{
	if (c == 1)
	{
		color = { 255, 255, 255, 255 };
	}
	else
	{
		color = { 0, 0, 0, 255 };
	}
}

namespace DisplayAndKeyboard_Manager
{

	bool keymap[KEYMAP_SIZE];

	SDL_Renderer* DisplayAndKeyboard_Manager::renderer = nullptr;
	SDL_Window* window = nullptr;
	std::vector< DRW_COORD > DisplayAndKeyboard_Manager::coords_buffer;
	bool DisplayAndKeyboard_Manager::screenMatrix[HEIGHT][WIDTH];



	void DisplayAndKeyboard_Manager::initDisplay()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		DisplayAndKeyboard_Manager::window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		if (DisplayAndKeyboard_Manager::window == NULL)
		{
			std::cerr << "Couldn't create window: " << SDL_GetError() << "\n";
			exit(-1);
		}
		
		DisplayAndKeyboard_Manager::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


		for (int i = 0; i < HEIGHT; i++) //Init screenMatrix
		{
			for (int j = 0; j < WIDTH; j++)
			{
				DisplayAndKeyboard_Manager::screenMatrix[i][j] = 0;
			}
		}

		for (int i = 0; i < KEYMAP_SIZE; i++) //Init keymap
		{
			DisplayAndKeyboard_Manager::keymap[i] = false;
		}
	}

	bool DisplayAndKeyboard_Manager::isPressed(uByte key)
	{
		return DisplayAndKeyboard_Manager::keymap[key];
	}



	void DisplayAndKeyboard_Manager::drawMatrix(int offset)
	{
		if (!coords_buffer.empty())
		{

			for (int i = 0; i < coords_buffer.size(); i++)
			{
				SDL_SetRenderDrawColor(DisplayAndKeyboard_Manager::renderer,
					coords_buffer[i].color.r,
					coords_buffer[i].color.g,
					coords_buffer[i].color.b,
					coords_buffer[i].color.a);

				SDL_Rect rect = { coords_buffer[i].y_coord * offset, coords_buffer[i].x_coord * offset, offset, offset };
				SDL_RenderFillRect(DisplayAndKeyboard_Manager::renderer, &rect);
			}

			coords_buffer.clear();
		}
	}

	void DisplayAndKeyboard_Manager::endDisplay()
	{
		SDL_DestroyRenderer(DisplayAndKeyboard_Manager::renderer);
		SDL_DestroyWindow(DisplayAndKeyboard_Manager::window);
		SDL_Quit();
	}
};