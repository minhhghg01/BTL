#include "Text.h"
#include <SDL_ttf.h>
#include "common.h"

void showText(SDL_Renderer* renderer,std::string msg,const int size,SDL_Color cl,SDL_Rect dsc){
    if(msg == "") return;

    TTF_Font* font = TTF_OpenFont(PATH_FONT.c_str(),size);

    if(font == nullptr) {
        std::cout<<SDL_GetError();
        exit(20);
    }
    SDL_Surface* load = TTF_RenderText_Solid(font,msg.c_str(),cl);
    SDL_Texture* res;
    if(load == nullptr) {
        std::cout<<msg<<'\n';
        std::cout<<"TTF_RenderText_Solid Error: "<<TTF_GetError();
        exit(3);
    }else{
        res = SDL_CreateTextureFromSurface(renderer,load);
    }

    if(res == nullptr) {
        std::cout<<SDL_GetError();
        exit(6);
    }else{

        int w,h;
        SDL_QueryTexture(res,nullptr,nullptr,&w,&h);
        dsc.x+= (dsc.w - w)/2;
        dsc.y+= (dsc.h - h)/2;
        dsc.w = w;
        dsc.h = h;
        SDL_RenderCopy(renderer,res,nullptr,&dsc);


    }

    SDL_FreeSurface(load);
    SDL_DestroyTexture(res);
    TTF_CloseFont(font);

    font = nullptr;
    load = nullptr;
    res = nullptr;
}
