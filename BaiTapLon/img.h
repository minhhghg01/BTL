#pragma once

#include <SDL_image.h>
#include <SDL.h>
#include <string>


SDL_Texture* loadIMG(std::string path , SDL_Renderer* renderer);
void showIMG(std::string path, SDL_Renderer* renderer, SDL_Rect rect);
