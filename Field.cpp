#include "Field.h"

Field::Field(SDL_Renderer* renderer, SDL_Texture* field, SDL_Texture* tiles, SDL_Texture* board, SDL_Texture* next_tiles)
{
	this->renderer = renderer;
	this->field = field;
	this->tiles = tiles;
	this->board = board;
	this->next_tiles = next_tiles;
	next_tile = static_cast<TILE_TYPE>(rand() % 7 + 1);
	c_tile;
	score = 0;
	resetTile();
	resetMesh();
}

void Field::resetMesh()
{
	for (int i = 0; i < TILE_WIDTH; i++)
	{
		for (int j = 0; j < TILE_HEIGHT; j++)
		{
			mesh[i][j] = NONE;
		}
	}
}

bool Field::tileDown()
{
	for (int i = 0; i < 4; i++)
	{
		if (c_tile.y[i] == 0 || mesh[c_tile.x[i]][c_tile.y[i] - 1] != NONE)
		{
			return true;
		}
	}
	return false;
}

void Field::handleInput(SDL_Event& e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		c_tile.moveLeft();
		if (inCollision())
		{
			c_tile.moveRight();
		}
		break;
	case SDLK_RIGHT:
		c_tile.moveRight();
		if (inCollision())
		{
			c_tile.moveLeft();
		}
		break;
	case SDLK_UP:
		c_tile.rotateRight();
		if (inCollision())
		{
			c_tile.rotateLeft();
		}
		break;
	case SDLK_DOWN:
		if (!tileDown())
		{
			c_tile.fall();
			score += 1;
		}
		break;
	case SDLK_SPACE:
		while (!tileDown())
		{
			c_tile.fall();
			score += 2;
		}
		break;
	default:
		break;
	}
}

void Field::tile_fall()
{
	c_tile.fall();
}

void Field::resetTile()
{
	srand(time(NULL));
	c_tile.type = next_tile;
	next_tile = static_cast<TILE_TYPE>(rand() % 7 + 1);
	score += 20;

	switch (c_tile.type)
	{
	case I:
		c_tile.x[0] = 3;
		c_tile.x[1] = 4;
		c_tile.x[2] = 5;
		c_tile.x[3] = 6;

		c_tile.y[0] = 19;
		c_tile.y[1] = 19;
		c_tile.y[2] = 19;
		c_tile.y[3] = 19;

		c_tile.cx = 4;
		c_tile.cy = 19;
		break;
	case O:
		c_tile.x[0] = 4;
		c_tile.x[1] = 5;
		c_tile.x[2] = 4;
		c_tile.x[3] = 5;

		c_tile.y[0] = 19;
		c_tile.y[1] = 19;
		c_tile.y[2] = 18;
		c_tile.y[3] = 18;

		c_tile.cx = 4;
		c_tile.cy = 19;
		break;
	case T:
		c_tile.x[0] = 3;
		c_tile.x[1] = 4;
		c_tile.x[2] = 5;
		c_tile.x[3] = 4;

		c_tile.y[0] = 19;
		c_tile.y[1] = 19;
		c_tile.y[2] = 19;
		c_tile.y[3] = 18;

		c_tile.cx = 4;
		c_tile.cy = 19;
		break;
	case S:
		c_tile.x[0] = 3;
		c_tile.x[1] = 4;
		c_tile.x[2] = 4;
		c_tile.x[3] = 5;

		c_tile.y[0] = 18;
		c_tile.y[1] = 18;
		c_tile.y[2] = 19;
		c_tile.y[3] = 19;

		c_tile.cx = 4;
		c_tile.cy = 18;
		break;
	case Z:
		c_tile.x[0] = 4;
		c_tile.x[1] = 5;
		c_tile.x[2] = 5;
		c_tile.x[3] = 6;

		c_tile.y[0] = 19;
		c_tile.y[1] = 19;
		c_tile.y[2] = 18;
		c_tile.y[3] = 18;

		c_tile.cx = 5;
		c_tile.cy = 18;
		break;
	case J:
		c_tile.x[0] = 4;
		c_tile.x[1] = 4;
		c_tile.x[2] = 5;
		c_tile.x[3] = 6;

		c_tile.y[0] = 19;
		c_tile.y[1] = 18;
		c_tile.y[2] = 18;
		c_tile.y[3] = 18;

		c_tile.cx = 5;
		c_tile.cy = 18;
		break;
	case L:
		c_tile.x[0] = 3;
		c_tile.x[1] = 4;
		c_tile.x[2] = 5;
		c_tile.x[3] = 5;

		c_tile.y[0] = 18;
		c_tile.y[1] = 18;
		c_tile.y[2] = 18;
		c_tile.y[3] = 19;

		c_tile.cx = 4;
		c_tile.cy = 18;
		break;
	case NONE:
		break;
	}
}

bool Field::inCollision()
{
	if (isTooDown() || isTooLeft() || isTooRight() || isTooUp())
	{
		return true;
	}

	for (int i = 0; i < 4; i++)
	{
		if (mesh[c_tile.x[i]][c_tile.y[i]] != NONE)
		{
			return true;
		}
	}
	return false;
}

bool Field::isTooLeft()
{
	for (int i = 0; i < 4; i++)
	{
		if (c_tile.x[i] < 0)
		{
			return true;
		}
	}
	return false;
}

bool Field::isTooRight()
{
	for (int i = 0; i < 4; i++)
	{
		if (c_tile.x[i] >= TILE_WIDTH)
		{
			return true;
		}
	}
	return false;
}

bool Field::isTooDown()
{
	for (int i = 0; i < 4; i++)
	{
		if (c_tile.y[i] < 0)
		{
			return true;
		}
	}
	return false;
}

bool Field::isTooUp()
{
	for (int i = 0; i < 4; i++)
	{
		if (c_tile.y[i] >= TILE_HEIGHT)
		{
			return true;
		}
	}
	return false;
}

bool Field::checkLine(unsigned short int line)
{
	for (int i = 0; i < TILE_WIDTH; i++)
	{
		if (mesh[i][line] == NONE)
		{
			return false;
		}

	}
	return true;

}

void Field::deleteLine(unsigned short int line)
{
	for (int j = line; j < TILE_HEIGHT-1; j++)
	{
		for (int i = 0; i < TILE_WIDTH; i++)
		{
			mesh[i][j] = mesh[i][j + 1];
		}
	}
	for (int i = 0; i < TILE_WIDTH; i++)
	{
		mesh[i][TILE_HEIGHT-1] = NONE;
	}
}

void Field::handleFullLines()
{
	int counter = 0;
	for (int j = 0; j < TILE_HEIGHT; j++)
	{
		while (checkLine(j))
		{
			deleteLine(j);
			counter++;
		}
	}

	switch (counter)
	{
	case 0:
		break;
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 600;
		break;
	case 4:
		score += 1000;
		break;
	default:
		break;
	}
}

void Field::renderField()
{
	SDL_Rect field_rect;
	field_rect.x = 0;
	field_rect.y = UPPER_LINE;
	SDL_QueryTexture(this->field, nullptr, nullptr, &field_rect.w, &field_rect.h);
	SDL_RenderCopy(this->renderer, this->field, NULL, &field_rect);

	SDL_Rect tile_rect = { 0, 0, WIDTH_OF_TILE, WIDTH_OF_TILE };
	SDL_Rect tile_clip = { 0, 0, WIDTH_OF_TILE, WIDTH_OF_TILE };
	for (int i = 0; i < TILE_WIDTH; i++)
	{
		for (int j = 0; j < TILE_HEIGHT; j++)
		{
			switch (this->mesh[i][j])
			{
			case I:
				tile_clip.x = 0;
				break;
			case J:
				tile_clip.x = WIDTH_OF_TILE;
				break;
			case L:
				tile_clip.x = WIDTH_OF_TILE * 2;
				break;
			case O:
				tile_clip.x = WIDTH_OF_TILE * 3;
				break;
			case S:
				tile_clip.x = WIDTH_OF_TILE * 4;
				break;
			case T:
				tile_clip.x = WIDTH_OF_TILE * 5;
				break;
			case Z:
				tile_clip.x = WIDTH_OF_TILE * 6;
				break;
			case NONE:
				tile_clip.x = WIDTH_OF_TILE * 7;
				break;
			default:
				break;
			}

			tile_rect.x = SIDELINE + i * WIDTH_OF_TILE;
			tile_rect.y = SIDELINE + UPPER_LINE + (TILE_HEIGHT - j - 1) * WIDTH_OF_TILE;
			SDL_RenderCopy(this->renderer, this->tiles, &tile_clip, &tile_rect);
		}
	}
}

void Field::renderCurrentTile()
{
	SDL_Rect tile_rect = { 0, 0, WIDTH_OF_TILE, WIDTH_OF_TILE };
	SDL_Rect tile_clip = { 0, 0, WIDTH_OF_TILE, WIDTH_OF_TILE };

	switch (c_tile.type)
	{
	case I:
		tile_clip.x = 0;
		break;
	case J:
		tile_clip.x = WIDTH_OF_TILE;
		break;
	case L:
		tile_clip.x = WIDTH_OF_TILE * 2;
		break;
	case O:
		tile_clip.x = WIDTH_OF_TILE * 3;
		break;
	case S:
		tile_clip.x = WIDTH_OF_TILE * 4;
		break;
	case T:
		tile_clip.x = WIDTH_OF_TILE * 5;
		break;
	case Z:
		tile_clip.x = WIDTH_OF_TILE * 6;
		break;
	case NONE:
		tile_clip.x = WIDTH_OF_TILE * 7;
		break;
	default:
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		tile_rect.x = SIDELINE + c_tile.x[i] * WIDTH_OF_TILE;
		tile_rect.y = SIDELINE + UPPER_LINE + (TILE_HEIGHT - c_tile.y[i] - 1) * WIDTH_OF_TILE;
		SDL_RenderCopy(this->renderer, this->tiles, &tile_clip, &tile_rect);
	}
}

void Field::renderBoard1()
{
	SDL_Rect tile_rect = { 0, 0, 0, 0 };
	SDL_Rect tile_clip = { 0, 0, 0, 0 };

	switch (next_tile)
	{
	case I:
		tile_clip.x = 0;
		tile_clip.y = 0;
		tile_clip.w = 4 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case J:
		tile_clip.x = 0;
		tile_clip.y = 2 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 3 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case L:
		tile_clip.x = 0;
		tile_clip.y = 4 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 3 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case O:
		tile_clip.x = 0;
		tile_clip.y = 6 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 2 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case S:
		tile_clip.x = 0;
		tile_clip.y = 8 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 3 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case T:
		tile_clip.x = 0;
		tile_clip.y = 10 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 3 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case Z:
		tile_clip.x = 0;
		tile_clip.y = 12 * WIDTH_OF_SMALL_TILE;
		tile_clip.w = 3 * WIDTH_OF_SMALL_TILE;
		tile_clip.h = 2 * WIDTH_OF_SMALL_TILE;
		break;
	case NONE:
		break;
	default:
		break;
	}

	tile_rect.x = SCREEN_WIDTH / 4 - tile_clip.w / 2;
	tile_rect.y = UPPER_LINE / 2 - tile_clip.h / 2;
	tile_rect.w = tile_clip.w;
	tile_rect.h = tile_clip.h;
	SDL_RenderCopy(this->renderer, this->next_tiles, &tile_clip, &tile_rect);
}

void Field::renderBoard2()
{
	std::stringstream err_msg;
	std::stringstream text;
	std::string text_score;
	text << score;
	text_score = text.str();

	SDL_Color white = { 255, 255, 255 };

	SDL_Rect score_rect;

	TTF_Font* font = TTF_OpenFont("fonts/calibri.ttf", TEXT_SIZE);
	if (font == nullptr)
	{
		err_msg << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	SDL_Surface* score_surface = TTF_RenderText_Solid(font, text_score.c_str(), white);
	if (score_surface == nullptr)
	{
		TTF_CloseFont(font);
		err_msg << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	SDL_Texture* score_pict = SDL_CreateTextureFromSurface(renderer, score_surface);
	if (score_pict == nullptr)
	{
		SDL_FreeSurface(score_surface);
		TTF_CloseFont(font);
		err_msg << "Unable to create texture from renderer text! SDL Error: " << SDL_GetError() << std::endl;
		throw TetrisException(err_msg.str());
	}

	SDL_FreeSurface(score_surface);
	TTF_CloseFont(font);

	SDL_QueryTexture(score_pict, nullptr, nullptr, &score_rect.w, &score_rect.h);
	score_rect.x = SCREEN_WIDTH / 4 * 3 - score_rect.w / 2;
	score_rect.y = UPPER_LINE/2 - score_rect.h / 2;

	SDL_RenderCopy(this->renderer, score_pict, NULL, &score_rect);
	SDL_DestroyTexture(score_pict);
}

void Field::renderBoards()
{
	SDL_Rect board_rect = { 0, 0, SCREEN_WIDTH / 2, UPPER_LINE };
	for (int i = 0; i < 2; i++)
	{
		board_rect.x = i * SCREEN_WIDTH / 2;
		SDL_RenderCopy(this->renderer, this->board, NULL, &board_rect);
	}

	renderBoard1();
	renderBoard2();

}

void Field::printTile()
{
	for (int i = 0; i < 4; i++)
	{
		mesh[c_tile.x[i]][c_tile.y[i]] = c_tile.type;
	}
}

void Field::renderAll()
{
	renderField();
	renderCurrentTile();
	renderBoards();
}