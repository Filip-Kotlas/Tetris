#include "Functions.h"
#include "Field.h"

int main(int argc, char* args[])
{
	try
	{
		SDL_Window* main_window = nullptr;
		SDL_Renderer* main_renderer = nullptr;

		init(main_window, main_renderer);

		SDL_Texture* main_field = loadFromFile(main_renderer, "pictures/field.png");
		SDL_Texture* main_tiles = loadFromFile(main_renderer, "pictures/tiles.png");
		SDL_Texture* main_logo = loadFromFile(main_renderer, "pictures/logo.png");
		SDL_Texture* main_board = loadFromFile(main_renderer, "pictures/board.png");
		SDL_Texture* main_next_tiles = loadFromFile(main_renderer, "pictures/next_tiles.png");

		int score = 0;
		SDL_Color white = { 255, 255, 255 };
		SDL_Color black = { 0, 0, 0 };

		renderToCentre(main_renderer, main_logo, 0, 0);
		SDL_RenderPresent(main_renderer);
		SDL_Delay(START_TIME);

		score = gameRun(main_renderer, main_field, main_tiles, main_board, main_next_tiles);  //zde probiha hra

		SDL_Texture* final_message = loadText(main_renderer, "Your score is: ", 30, white);
		std::stringstream score_string;
		score_string << score;
		SDL_Texture* final_score = loadText(main_renderer, score_string.str(), 30, white);

		if (score >= 0)
		{
			drawRect(main_renderer, FINAL_SCORE_X, FINAL_SCORE_Y, FINAL_SCORE_W, FINAL_SCORE_H, black, white);
			renderToCentre(main_renderer, final_message, 0, -20);
			renderToCentre(main_renderer, final_score, 0, +20);
			SDL_RenderPresent(main_renderer);
			waitUntillExit();
		}
	

		SDL_DestroyTexture(main_field);
		SDL_DestroyTexture(main_tiles);
		SDL_DestroyTexture(main_logo);
		SDL_DestroyTexture(final_message);
		SDL_DestroyTexture(final_score);
		cleanUp(main_window, main_renderer);
	}
	catch (TetrisException& exception)
	{
		std::cout << "Error occured." << std::endl;
		std::cout << exception.what();
	}
	catch (...)
	{
		std::cout << "Error occured" << std::endl;
	}

	return 0;
}