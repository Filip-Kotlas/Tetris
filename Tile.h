#ifndef __TILE_H__
#define __TILE_H__

#include "Constants.h"

class Tile
{
private:
	TILE_TYPE type;
	short int cx;
	short int cy;
	short int x[4];
	short int y[4];
public:
	Tile();
	void fall();
	void rotateRight();
	void rotateLeft();
	void moveRight();
	void moveLeft();
	void moveUp();
	friend class Field;
};

#endif //__TILE_H__