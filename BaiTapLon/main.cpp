#include<bits/stdc++.h>
#include<SDL.h>
#include <SDL_ttf.h>
#include"Text.h"
#include "common.h"
#include "G2048.h"
using namespace std;

//ham choi game
bool playGame(SDL_Renderer* ren, G2048 game)
{
    SDL_Event e;
    bool isrunning = true;

    game.init();
    game.random();
    game.random();
    game.print(ren);
    while( isrunning )
    {

        setRenderColor(ren,BLACK_COLOR);
        SDL_RenderClear(ren);

        while(SDL_PollEvent(&e)){
                switch(e.type){
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:

                        switch(e.key.keysym.sym){
                        case SDLK_r:
                            {
                                return playGame(ren, game);
                            }
                        case SDLK_w:
                        case SDLK_UP:
                            game.upMove();
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            game.downMove();
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            game.leftMove();
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            game.rightMove();
                            break;
                        case SDLK_ESCAPE:
                            isrunning = false;
                            break;
                        }

                        break;

                    default:
                            break;
                }

                if( game.empty() )
                    game.random();


                if(game.gameOver()) return 0;
                if( game.gameWin() )return 1;
            }

            game.print(ren);
            cout << "\n";

            SDL_RenderPresent(ren);
            SDL_Delay(100);
    }
}

int main(int agrc, char* argv[])
{
    srand(time(NULL));

    G2048 game;
    SDL_Window* win;
    SDL_Renderer* ren;

    TTF_Font* font = nullptr;
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;

    //ktao sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    //tao cua so sdl
    SDL_CreateWindowAndRenderer(w, h, NULL, &win, &ren);

    SDL_SetWindowTitle(win, " 2^11 ");

    while( true ){
        //ktra choi thang hay thua
        bool winGame = playGame( ren, game );

        setRenderColor(ren,BLACK_COLOR);
        SDL_RenderClear(ren);
        SDL_Rect text;
        text = {0, 0, 600, 400};
        showText(ren,(winGame ? "You win <3 ":"You lose -_-"),50,WHITE_COLOR,text);
        text = {0, 50, 600, 400};
        showText(ren,"Press the R key to play again!",30,WHITE_COLOR,text);
        SDL_RenderPresent(ren);
        SDL_Event e;
        //ktra choi lai hay k
        while(1){
                while( !SDL_PollEvent(&e) );

                if(e.type == SDL_QUIT) return 0;

                if(e.type == SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym == SDLK_r) break;
                        if(e.key.keysym.sym == SDLK_ESCAPE) return 0;
                    }


        }
    }
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyRenderer( ren );
    SDL_DestroyWindow( win );

    SDL_Quit();
    TTF_Quit();
    return 0;

}

