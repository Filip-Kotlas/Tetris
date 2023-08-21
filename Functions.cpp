#include "Functions.h"

void init(SDL_Window*& Window, SDL_Renderer*& Renderer)
{
	std::stringstream err_msg;
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		err_msg << "SDL2 was not initialized. SDL_Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		err_msg << "SDL2_image was not initialized. IMG_Error: " << IMG_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}
	if (TTF_Init())
	{
		err_msg << "SDL2_ttf was not initialized. TTF_Error: " << TTF_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	Window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
	{
		err_msg << "Window was not created. SDL_Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == nullptr)
	{
		err_msg << "Renderer was not created. SDL_Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

}

SDL_Texture* loadFromFile(SDL_Renderer* renderer, std::string path)
{
	std::stringstream err_msg;

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		err_msg << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
		throw TetrisException(err_msg.str());
		return newTexture;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == nullptr)
	{
		err_msg << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

SDL_Texture* loadText(SDL_Renderer* renderer, std::string text, int size, SDL_Color color)
{
	std::stringstream err_msg;
	TTF_Font* font = TTF_OpenFont("fonts/calibri.ttf", size);
	if (font == nullptr)
	{
		err_msg << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
		throw TetrisException(err_msg.str());
		return nullptr;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (text_surface == nullptr)
	{
		err_msg << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		throw TetrisException(err_msg.str());
		return nullptr;
	}

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (text_texture == nullptr)
	{
		err_msg << "Unable to create texture from renderer text! SDL Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	return text_texture;
}

void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color_fill, SDL_Color color_frame)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, color_fill.r, color_fill.g, color_fill.b, 0);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, color_frame.r, color_frame.g, color_frame.b, 0);
	SDL_RenderDrawRect(renderer, &rect);
}

void cleanUp(SDL_Window*& Window, SDL_Renderer*& Renderer)
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = nullptr;
	Renderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int gameRun(SDL_Renderer* renderer, SDL_Texture* field_pict, SDL_Texture* tiles_pict, SDL_Texture* board_pict, SDL_Texture* next_tiles_pict)
{
	bool loss = false;
	SDL_Event e;
	bool quit = false;
	int timer = 0;

	Field field(renderer, field_pict, tiles_pict, board_pict, next_tiles_pict);


	while (!quit && !loss)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				field.handleInput(e);
			}
		}

		if (SDL_GetTicks() - timer > TIME_STEP)
		{
			if (field.tileDown())
			{
				field.printTile();
				field.resetTile();
				field.handleFullLines();
				if (field.tileDown())
				{
					loss = true;
				}
			}
			else
			{
				field.tile_fall();
			}
			timer = SDL_GetTicks();
		}

		field.renderAll();
		SDL_RenderPresent(renderer);
	}

	return quit ? -1 : field.getScore();
}

void renderToCentre(SDL_Renderer* renderer, SDL_Texture* picture, int x_offset, int y_offset)
{
	SDL_Rect centre;
	SDL_QueryTexture(picture, nullptr, nullptr, &centre.w, &centre.h);
	centre.x = (SCREEN_WIDTH - centre.w) / 2 + x_offset;
	centre.y = (SCREEN_HEIGHT - centre.h) / 2 + y_offset;
	SDL_RenderCopy(renderer, picture, nullptr, &centre);
}

void waitUntillExit()
{
	SDL_Event e;
	bool exit = false;
	while (!exit)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
		{
			exit = true;
		}
	}
}