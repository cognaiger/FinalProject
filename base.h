#ifndef BASE_H
#define BASE_H

// include everything we need
#include<iostream>
#include<vector>
#include<tchar.h>
#include<windows.h>

#include"SDL2/SDL.h"
#include"SDL2/SDL_image.h"
#include"SDL2/SDL_ttf.h"

// declare all static variable
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gSurface = NULL;
static SDL_Event gEvent;

// fps
const int FPS = 30;

// screen information
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 640;
const int SCREEN_BBP = 32;

// set of colors that specify transparent color
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

// tile map
#define TILE_SIZE 64
#define BLANK_TILE 0
#define COIN_TILE 4
#define SMALL_TREE 9
#define BIG_TREE 8

// divide map into 400x10 grid
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

// function handle movement status of character
typedef struct Input {
    int left;
    int right;
    int up;
    int down;
    int jump;
};


namespace SDLBase {
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void ApplySurface(SDL_Surface* src, SDL_Renderer* des, int x, int y);
    bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}


#endif