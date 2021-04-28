#pragma once
#include "_SDL.h"
#include "common.h"
class G2048{
public:
    void init();
    bool gameWin();
    bool gameOver();
    void leftMove();
    void rightMove();
    void upMove();
    void downMove();
    void random();
    void print(SDL_Renderer*&);
    bool empty() { return emp; }
    void free(void);

    SDL_Rect *dsc;
    SDL_Rect text[10];

private:
    int a[4][4];
    bool emp = true;
};

void setRenderColor(SDL_Renderer*&,const SDL_Color);
