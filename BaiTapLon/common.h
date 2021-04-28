#pragma once
#include <iostream>
#include <SDL.h>

#define BOARD_SIZE      4

#define BOARD_WIDTH		400
#define BOARD_X         50
#define BOARD_Y         10

const std::string PATH_FONT = "font-times-new-roman.ttf";

const int h = 402, w = 602;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color INDGOBLUE_COLOR = {75, 0, 130};
const SDL_Color PINK_COLOR = {200, 90, 90};

int getSingle(int,int,int);
