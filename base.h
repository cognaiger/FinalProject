#ifndef BASE_H
#define BASE_H

// include everything we need
#include<iostream>

#include"SDL2/SDL.h"
#include"SDL2/SDL_image.h"

// declare all static variable
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gSurface = NULL;
static SDL_Event gEvent;

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

// map that we render on screen
typedef struct Map {
    // X-coordinate that map begin
    int startX;
    // Y-coordinate that map begin
    int startY;

    // max X-coordinate
    int maxX;
    // max Y-coordinate
    int maxY;

    // array that contain text-map
    int tile[MAX_MAP_Y][MAX_MAP_X];

    char* fileName;
};

#endif