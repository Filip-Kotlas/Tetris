#include "Tile.h"

Tile::Tile()
{
	for (int i = 0; i < 4; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	cx = 0;
	cy = 0;
	type = NONE;
}

void Tile::fall()
{
	for (int i = 0; i < 4; i++)
	{
		y[i] -= 1;
	}
	cy -= 1;
}

void Tile::rotateRight()
{
	if (this->type == O)
	{
		return;
	}
	else
	{
		int px = 0;
		int py = 0;
		for (int i = 0; i < 4; i++)
		{
			px = x[i];
			py = y[i];
			x[i] = cx + py - cy;
			y[i] = cy + cx - px;
		}
		
	}
}

void Tile::rotateLeft()
{
	if (this->type == O)
	{
		return;
	}
	else
	{
		int px = 0;
		int py = 0;
		for (int i = 0; i < 4; i++)
		{
			px = x[i];
			py = y[i];
			x[i] = cx + cy - py;
			y[i] = cy + px - cx;

			if (x[i] < 0)
			{
				x[i] += 1;
				cx += 1;
			}
			if (x[i] >= TILE_WIDTH)
			{
				x[i] -= 1;
				cx -= 1;
			}
			if (y[i] < 0)
			{
				y[i] += 1;
				cy += 1;
			}
			if (y[i] > TILE_HEIGHT)
			{
				y[i] -= 1;
				cy -= 1;
			}
		}

	}
}

void Tile::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		x[i] += 1;
	}
	cx += 1;
}

void Tile::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		x[i] -= 1;
	}
	cx -= 1;
}

void Tile::moveUp()
{
	for (int i = 0; i < 4; i++)
	{
		y[i] += 1;
		cy += 1;
	}
}




