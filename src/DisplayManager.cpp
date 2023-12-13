#include "DisplayManager.h"

DRW_COORD::DRW_COORD(uByte x, uByte y, bool c)
	: x_coord(x), y_coord(y)
{
	if (c == 1)
	{
		color = { WHITE };
	}
	else
	{
		color = { BLACK };
	}
}


DisplayManager::DisplayManager()
	: renderer(nullptr), m_window(nullptr), screenMatrix(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		std::cerr << "Couldn't create window: " << SDL_GetError() << "\n";
		exit(-1);
	}

	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	screenMatrix = new bool*[HEIGHT];

	for (int i = 0; i < HEIGHT; i++) //Init screenMatrix
	{
		for (int j = 0; j < WIDTH; j++)
		{
			screenMatrix[i] = new bool[WIDTH];
		}
	}
}

DisplayManager::~DisplayManager()
{
	for (int i = 0; i < WIDTH; i++)
	{
		delete[] screenMatrix[i];
	}
	delete[] screenMatrix;

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
				coords_buffer[i].color.r,
				coords_buffer[i].color.g,
				coords_buffer[i].color.b,
				coords_buffer[i].color.a);

			SDL_Rect rect = { coords_buffer[i].y_coord * offset, coords_buffer[i].x_coord * offset, offset, offset };
			SDL_RenderFillRect(renderer, &rect);
		}

		coords_buffer.clear();
	}
}
