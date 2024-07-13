#include "DisplayManager.h"

dTEXT::dTEXT(const char* content, int x, int y, SDL_Color color, bool blend)
	: t_content(content),
	x(x), y(y),
	color(color),
	active(false),
	blend(blend),
	textPlace({x, y, 112, 52}) {}

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

void waitFPS(Uint32 delta, Uint32 desiredDelta)
{
	if (delta < desiredDelta)
	{
		SDL_Delay(desiredDelta - delta);
	}
}

DisplayManager::DisplayManager()
	: renderer(nullptr), m_window(nullptr), m_text(nullptr), m_font(nullptr), screenMatrix()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < NULL)
	{
		std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << "\n";
		exit(-1);
	}
	m_window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * OFFSET, HEIGHT * OFFSET, SDL_WINDOW_SHOWN);
	
	if (m_window == NULL)
	{
		std::cerr << "Couldn't create window: " << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-1);
	}

	if (TTF_Init() < NULL)
	{
		std::cerr << "Couldn't initialize TTF: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		exit(-1);
	}

	loadFont();

	clearDisplay();
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

DisplayManager::~DisplayManager()
{
	SDL_RenderClear(renderer);
	SDL_FreeSurface(m_text);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);

	TTF_Quit();
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

void DisplayManager::drawMatrix()
{
	if (!coords_buffer.empty())
	{
		for (auto& i : coords_buffer)
		{
			SDL_SetRenderDrawColor(renderer,
				i.pixel_color.r,
				i.pixel_color.g,
				i.pixel_color.b,
				i.pixel_color.a);

			SDL_Rect rect = { i.y_coord * OFFSET, i.x_coord * OFFSET, OFFSET, OFFSET };
			SDL_RenderFillRect(renderer, &rect);
		}

		coords_buffer.clear();
	}
}

void DisplayManager::writeText(dTEXT& text)
{
	if (text.active == true) return;

	if (text.blend == false)
	{
		clearTextPlace(text);
		SDL_SetRenderDrawColor(renderer, BLACK);

		SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, text.t_content.c_str(), text.color);

		SDL_Texture* text_to_draw = SDL_CreateTextureFromSurface(renderer, text_surface);

		SDL_RenderCopy(renderer, text_to_draw, NULL, &text.textPlace);

		SDL_FreeSurface(text_surface);
		SDL_DestroyTexture(text_to_draw);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, BLACK);
		SDL_RenderFillRect(renderer, &text.textPlace);
		m_text = TTF_RenderText_Blended(m_font, text.t_content.c_str(), SDL_Color({ WHITE }));

		SDL_Texture* text_to_draw = SDL_CreateTextureFromSurface(renderer, m_text);
		SDL_SetTextureAlphaMod(text_to_draw, text.color.a);

		SDL_RenderCopy(renderer, text_to_draw, NULL, &text.textPlace);

		SDL_FreeSurface(m_text);
		m_text = nullptr;
		SDL_DestroyTexture(text_to_draw);
	}

	text.active = true;
}

void DisplayManager::fillTextPlace(dTEXT& text)
{
	if (text.active == false) return;
	Uint8 alpha;

	int text_xpos = text.x / OFFSET;
	int text_ypos = text.y / OFFSET;

	for (int i = text_ypos; i < text_ypos + (text.textPlace.h / FILL_HEIGHT); i++)
	{
		for (int j = text_xpos; j < text_xpos + (text.textPlace.w / FILL_WIDTH); j++)
		{
			if (text.blend)
			{
				alpha = screenMatrix[i][j] * 0xFF;
			}
			else
			{
				alpha = 0xFF;
			}

			SDL_SetRenderDrawColor(renderer,
				screenMatrix[i][j] * 0xFF,
				screenMatrix[i][j] * 0xFF,
				screenMatrix[i][j] * 0xFF,
				alpha
			);

			SDL_Rect rect = { j * OFFSET, i * OFFSET, OFFSET, OFFSET};
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	text.active = false;
}

void DisplayManager::updateAlpha(dTEXT& text, bool speedup, bool slowdown)
{
	static bool toggle = false;
	Uint8 alphaDifference;

	if (speedup)
	{
		if (toggle)
		{
			alphaDifference = 1;
			toggle = false;
		}
		else
		{
			alphaDifference = 0;
			toggle = true;
		}
	}
	else if (slowdown)
	{
		alphaDifference = 2;
	}
	else
	{
		alphaDifference = 1;
	}

	if (text.color.a - alphaDifference > 0)
	{
		text.color.a -= alphaDifference;
	}
	else
	{
		return;
	}
}

void DisplayManager::updateSpeedText(dTEXT& text)
{
	writeText(text);
	fillTextPlace(text);
}

void DisplayManager::DisplayQuit()
{
	TTF_CloseFont(m_font);
}

void DisplayManager::loadFont()
{
	m_font = TTF_OpenFont(WIN_ARIAL_FONT_DIR, 72);

	if (m_font == NULL)
	{
		std::cerr << "Couldn't load font: " << TTF_GetError() << "\n";
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		SDL_Quit();
	}

}

void DisplayManager::clearTextPlace(dTEXT& text)
{
	int text_xpos = text.x / OFFSET;
	int text_ypos = text.y / OFFSET;

	SDL_SetRenderDrawColor(renderer, BLACK);

	for (int i = text_ypos; i < text_ypos + (text.textPlace.h / FILL_HEIGHT); i++)
	{
		for (int j = text_xpos; j < text_xpos + (text.textPlace.w / FILL_WIDTH); j++)
		{
			SDL_Rect rect = { j * OFFSET, i * OFFSET, OFFSET, OFFSET };
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
