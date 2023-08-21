#ifndef __FIELD_H__
#define __FIELD_H__

#include "Constants.h"
#include "Tile.h"

class Field
{
private:
	TILE_TYPE mesh[TILE_WIDTH][TILE_HEIGHT];
	SDL_Texture* field;
	SDL_Texture* tiles;
	SDL_Texture* board;
	SDL_Texture* next_tiles;
	SDL_Renderer* renderer;
	TILE_TYPE next_tile;
	Tile c_tile;	 //current tile			
	int score;

public:
	Field(SDL_Renderer* renderer, SDL_Texture* field, SDL_Texture* tiles, SDL_Texture* board, SDL_Texture* next_tiles);
	
	void resetMesh();

	bool tileDown();
	bool inCollision();
	void printTile();
	void tile_fall();
	void resetTile();

	bool isTooLeft();
	bool isTooRight();
	bool isTooDown();
	bool isTooUp();

	void handleInput(SDL_Event& e);

	bool checkLine(unsigned short int line);
	void deleteLine(unsigned short int line);
	void handleFullLines();

	void renderField();
	void renderCurrentTile();
	void renderBoard1();
	void renderBoard2();
	void renderBoards();
	void renderAll();

	int getScore() { return score; }

};

#endif //__FIELD_H__