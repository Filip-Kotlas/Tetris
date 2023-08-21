#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <sstream>
#include <ctime>

#include "TetrisException.h"


const unsigned int TILE_WIDTH = 10;
const unsigned int TILE_HEIGHT = 20;

const unsigned int WIDTH_OF_TILE = 24;
const unsigned int WIDTH_OF_SMALL_TILE = 16;
const unsigned int SIDELINE = 10;
const unsigned int UPPER_LINE = 60;

const unsigned int SCREEN_WIDTH = TILE_WIDTH * WIDTH_OF_TILE + 2 * SIDELINE;
const unsigned int SCREEN_HEIGHT = TILE_HEIGHT * WIDTH_OF_TILE + SIDELINE * 2 + UPPER_LINE;

const unsigned int FINAL_SCORE_W = 195;
const unsigned int FINAL_SCORE_H = 100;
const unsigned int FINAL_SCORE_X = (SCREEN_WIDTH - FINAL_SCORE_W) / 2;
const unsigned int FINAL_SCORE_Y = (SCREEN_HEIGHT- FINAL_SCORE_H) / 2;

const unsigned int TEXT_SIZE = 30;

const unsigned int START_TIME = 2000;
const unsigned int TIME_STEP = 1000;

enum TILE_TYPE
{
	NONE,
	I,
	O,
	T,
	S,
	Z,
	J,
	L
};



#endif //__CONSTANTS_H__