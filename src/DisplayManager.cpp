#include "DisplayManager.h"

DRW_COORD::DRW_COORD(uByte x, uByte y, bool color)
	: x_coord(x), y_coord(y)
{
	if (color == 1)
	{
		pixel_color = SDL_Color(WHITE);
	}
	else
	{
		pixel_color = SDL_Color(BLACK);
	}
}


DisplayManager::DisplayManager()
	: renderer(nullptr), m_window(nullptr), screenMatrix()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * 8, HEIGHT * 8, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		std::cerr << "Couldn't create window: " << SDL_GetError() << "\n";
		this->~DisplayManager();
		exit(-1);
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			screenMatrix[i][j] = 0;
		}
	}

	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

DisplayManager::~DisplayManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void DisplayManager::drawMatrix(int offset)
{
	if (!coords_buffer.empty())
	{

		for (int i = 0; i < coords_buffer.size(); i++)
		{
			SDL_SetRenderDrawColor(renderer,
				coords_buffer[i].pixel_color.r,
				coords_buffer[i].pixel_color.g,
				coords_buffer[i].pixel_color.b,
				coords_buffer[i].pixel_color.a);

			SDL_Rect rect = { coords_buffer[i].y_coord * offset, coords_buffer[i].x_coord * offset, offset, offset };
			SDL_RenderFillRect(renderer, &rect);

		}

		coords_buffer.clear();
	}
}
