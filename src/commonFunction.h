
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<iostream>
#include<string>
#include<SDL.h>
#include<fstream>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gscreen = NULL;
static SDL_Event gEvent;

//screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;
const int SCREEN_BPP = 32;

// The dimensions of the level
const int LEVEL_WIDTH = 2850;
const int LEVEL_HEIGHT = 2790;

//the dimensions of tile
const int TILE_SIZE = 30;
const int MAX_MAP_X = 95;
const int MAX_MAP_Y = 93;

//fps
const int FRAME_PER_SECOND = 16;

//toc do di chuyen
const int BALL_VEL = 6;

//mixer
#define MIX_CHANNEL -1
#define NOT_REPEATITIVE 0

typedef struct Map
{
    int start_x ;
    int start_y ;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};



#endif