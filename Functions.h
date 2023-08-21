#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Constants.h"
#include "Field.h"

void init(SDL_Window*& Window, SDL_Renderer*& Renderer);

SDL_Texture* loadFromFile(SDL_Renderer* renderer, std::string path);

SDL_Texture* loadText(SDL_Renderer* renderer, std::string text, int size, SDL_Color color);

void drawRect(SDL_Renderer* renderer,int x, int y, int w, int h, SDL_Color color_fill, SDL_Color color_frame);

void cleanUp(SDL_Window*& Window, SDL_Renderer*& Renderer);

int gameRun(SDL_Renderer* renderer, SDL_Texture* field_pict, SDL_Texture* tiles_pict, SDL_Texture* board_pict, SDL_Texture* next_tiles_pict);

void renderToCentre(SDL_Renderer* renderer, SDL_Texture* picture, int x_offset, int y_offset);

void waitUntillExit();


#endif __FUNCTIONS_H__