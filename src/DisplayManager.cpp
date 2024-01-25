#include "DisplayManager.h"

DRW_COORD::DRW_COORD(uByte x, uByte y, bool color)
	: x_coord(x), y_coord(y)
{
	if (color == 1)
	{
		pixel_color = { WHITE };
	}
	else
	{
		pixel_color = { BLACK };
	}
}


DisplayManager::DisplayManager()
	: renderer(nullptr), m_window(nullptr), m_font(nullptr), text_alpha(0), textBox({ 0, 0, 104, 56 }), screenMatrix()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * 8, HEIGHT * 8, SDL_WINDOW_SHOWN);
	
	if (m_window == NULL)
	{
		std::cerr << "Couldn't create window: " << SDL_GetError() << "\n";
		this->~DisplayManager();
		exit(-1);
	}

	if (TTF_Init() < NULL)
	{
		std::cerr << "Couldn't initialize TTF: " << SDL_GetError() << "\n";
		this->~DisplayManager();
		exit(-1);
	}

	loadFont();

	clearDisplay();
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

DisplayManager::~DisplayManager()
{
	TTF_CloseFont(m_font);
	SDL_FreeSurface(m_text);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void DisplayManager::clearDisplay()
{
	SDL_SetRenderDrawColor(renderer, BLACK);
	SDL_RenderClear(renderer);

	coords_buffer.clear();
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			screenMatrix[i][j] = 0;
		}
	}
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


void DisplayManager::loadFont()
{
	m_font = TTF_OpenFont("../assets/arial_font.ttf", 72);
	if (m_font == NULL)
	{
		std::cerr << "Couldn't load font: " << SDL_GetError() << "\n";
		this->~DisplayManager();
		exit(-1);
	}
}

void DisplayManager::writeText(const char* text)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &textBox);
	m_text = TTF_RenderText_Blended(m_font, text, SDL_Color({ WHITE }));
	
	SDL_Texture* text_to_draw = SDL_CreateTextureFromSurface(renderer, m_text);
	SDL_SetTextureAlphaMod(text_to_draw, text_alpha);
	SDL_RenderCopy(renderer, text_to_draw, NULL, &textBox);
	
	SDL_FreeSurface(m_text);
	SDL_DestroyTexture(text_to_draw);
}

void DisplayManager::fillTextPlace(int offset)
{
	for (int i = 0; i < FILL_HEIGHT; i++)
	{
		for (int j = 0; j < FILL_WIDTH; j++)
		{
			SDL_SetRenderDrawColor(renderer,
				screenMatrix[i][j] * 0xFF,
				screenMatrix[i][j] * 0xFF,
				screenMatrix[i][j] * 0xFF,
				screenMatrix[i][j] * 0xFF);

			SDL_Rect rect = { j * offset, i * offset, offset, offset};
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
