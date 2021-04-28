#include "G2048.h"
#include "Text.h"
#include "common.h"
#include <bits/stdc++.h>

void G2048::init(){
    memset(a, 0, sizeof(a));
    dsc = new SDL_Rect[16];

    for(int i = 0;i<16;i++){
        dsc[i].w = dsc[i].h = 100;
        dsc[i].y = dsc[i].x = 1;
    }

    for(int i = 0;i<4;i++){
        for(int t = 0;t<4;t++){
            dsc[getSingle(i,t,4)].x +=100*i;
            dsc[getSingle(i,t,4)].y +=100*t;
        }
    }
    for(int i=0;i<10;i++)
    {
        text[i].x = 450;
        text[i].w = 100;
        text[i].h = 30;
    }
    text[0].y = 50;
    for(int i=1;i<10;i++)
    {
        text[i].y = text[i-1].y + 35;
    }
}

void G2048::free(void){
    delete[] dsc;
}

void G2048::upMove(){

    for( int j = 0; j < 4; j++)
    {
        int k = 0;
        for(int i = 0; i < 4; i++)
                if(a[i][j] != 0) a[k++][j] = a[i][j];

        for(; k < 4; k++)
            if(a[k][j])emp = true, a[k][j] = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
            if(a[i][j] == a[i + 1][j] && a[i][j])
            {
                emp = true; a[i][j] *= 2;
                for( int u = i + 1; u < 3; u++) a[u][j] = a[u + 1][j];
                a[3][j] = 0;
            }
    }
}

void G2048::downMove() {
    for( int j = 0; j < 4; j++)
    {
        int k = 0;
        for(int i = 3; i >= 0; i--)
            if(a[i][j] != 0) a[3-k][j] = a[i][j], k++;

        for(; k < 4; k++)
            if(a[3 - k][j]) emp = true, a[3 - k][j] = 0;
    }

    for(int i = 3; i >= 0; i--)
    {
        for(int j = 0; j < 4; j++)
            if(a[i][j] == a[i - 1][j])
        {
            emp = true;
            a[i][j] *= 2;
            for( int u = i - 1; u > 0; u--) a[u][j] = a[u - 1][j];
            a[0][j] = 0;
        }
    }
}

void G2048::leftMove(){
    for( int i = 0; i < 4; i++)
    {
        int k = 0;
        for(int j = 0; j < 4; j++)
            if(a[i][j] != 0) a[i][k] = a[i][j], k++;
        while(k < 4) emp |= a[i][k], a[i][k] = 0, k++;
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0, k = 1; j < 4 - k; j++)
            if(a[i][j] == a[i][j + 1])
        {
            a[i][j] *= 2; emp = true;
            for( int u = j + 1; u < 3; u++) a[i][u] = a[i][u+1];
            a[i][3] = 0; k++;
        }
    }
}

void G2048::rightMove(){
    for( int i = 0; i <= 3; i++)
    {
        int k = 3;
        for(int j = 3; j >= 0; j--)
            if(a[i][j] != 0) a[i][k] = a[i][j], k--;
        while(k >= 0 ) emp |= a[i][k], a[i][k] = 0, k--;
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = 3, k = 1; j >= 0 + k; j--)
        if(a[i][j] == a[i][j - 1])
        {
            a[i][j] *= 2; emp = true;
            for( int u = j - 1; u > 0; u--) a[i][u] = a[i][u-1];
            a[i][0] = 0; k++;
        }
    }
}

void G2048::random(){
    emp = false;
    int val;
    int s = rand() % 100;
	if (s > 89) val = 4;
	else val = 2;

    do{
        int x = rand() % 4;
        int y = rand() % 4;
        if(a[x][y] == 0) {
            a[x][y] = val;
            return;
        }
    }while( true );
}

bool G2048::gameOver(){
    for( int i = 0; i < 4; i++)
        for( int j = 0; j < 4; j++)
            if(!a[i][j]) return 0;

    for( int i = 0; i < 3; i++ )
        for(int j = 0; j < 4; j++)
            if(a[i][j] == a[i+1][j])  return 0;

    for( int i = 0; i < 4; i++ )
        for(int j = 0; j < 3; j++)
            if(a[i][j] == a[i][j+1])  return 0;

    return 1;
}

bool G2048::gameWin(){
    for( int i = 0; i < 4; i++ )
        for ( int j = 0; j < 4 ; j++ )
            if(a[i][j] == 2048 ) return 1;
    return 0;
}

void G2048::print(SDL_Renderer*& renderer){

    setRenderColor(renderer,WHITE_COLOR);
    SDL_RenderDrawRects(renderer,dsc,16);

    std::string num = "";
    SDL_Color cl;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++){
            num = (a[i][j] != 0 ?  std::to_string(a[i][j]):"");
            switch(a[i][j]){
            case 2:
                cl = WHITE_COLOR;
                break;
            case 4:
                cl = BLUE_COLOR;
                break;
            case 8:
                cl = {0,0,128};
                break;
            case 16:
                cl = GREEN_COLOR;
                break;
            case 32:
                cl = LIME_COLOR;
                break;
            case 64:
                cl = {0,128,255};
                break;
            case 128:
                cl = {0,128,128};
                break;
            case 256:
                cl = {0,255,255};
                break;
            case 512:
                cl = PINK_COLOR;
                break;
            case 1024:
                cl = ORANGE_COLOR;
                break;
            case 2048:
                cl = RED_COLOR;
                break;
            default:
                cl = WHITE_COLOR;
                break;
            }
            showText(renderer,num,35,cl,dsc[getSingle(j,i,4)]);
        }
    }
    showText(renderer,"Intruction: ",20,RED_COLOR,text[0]);
    showText(renderer,"Turn Left: A",15,ORANGE_COLOR,text[1]);
    showText(renderer,"Turn Right: D",15,YELLOW_COLOR,text[2]);
    showText(renderer,"Go Down: S",15,GREEN_COLOR,text[3]);
    showText(renderer,"Go Up: W",15,BLUE_COLOR,text[4]);
    showText(renderer,"Or use arrow keys to play",15,INDGOBLUE_COLOR,text[5]);
    showText(renderer,"Press 'ESC' to exit!",15,PURPLE_COLOR,text[6]);
    showText(renderer,"Press the 'R' key to play again!",15,PINK_COLOR,text[7]);
}

//xet mau
void setRenderColor(SDL_Renderer*& renderer,const SDL_Color cl){
    SDL_SetRenderDrawColor(renderer,cl.r,cl.g,cl.b,cl.a);
}


