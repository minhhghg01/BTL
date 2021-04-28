#include "img.h"
#include <iostream>

SDL_Texture* loadIMG(std::string path , SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if ( loadedSurface == NULL )
        std::cout << "Error: IMG_Load() \n";
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );

        if( newTexture == NULL )
            std::cout << "Error: SDL_CreateTextureFromSurface() \n";
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;

}

void showIMG(std::string path, SDL_Renderer* renderer, SDL_Rect rect)
{
    SDL_Texture* text = loadIMG(path, renderer);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture( text );
    SDL_RenderPresent(renderer);
}
