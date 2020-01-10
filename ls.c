#include "ls.h"
#include "sdl.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

struct pos {
    struct pos* next;
    int x;
    int y;
    double a;
};
#define Pos struct pos

struct parameters {
    double ang;
};
#define Param struct parameters

int match(char c) {
    switch(c) {
        case 'X':
            return 1;
        case 'F':
            return 0;
        default:
            return -1;
    }
}

void drawLine(int x0, int y0, int x1, int y1) {
    SDL_SetRenderDrawColor(app.renderer, 0x7c, 0xa7, 0xa2, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(app.renderer, x0, y0, x1, y1);
}

void calc(char c, Pos* p, Param par, int d) {
    if(p->y < 0) return;
    
    int ruleS[2] = {2, 23};
    char* words[] = {"FF", "F+[[X]-[FX-]]-F[-FX]+X"};

    int it = match(c);

    if(it >= 0 && d > 0) {
        for(int i = 0; i < ruleS[it]; i++) {
            calc(words[it][i], p, par, d - 1);
        }
    } else {
        Pos* ptr = NULL;
        Pos* p0 = p;
        int nx, ny;
        switch(c) {
            case 'X':
                nx = p->x - sin(p->a)*1;
                ny = p->y - cos(p->a)*1;
                drawLine(p->x, p->y, nx, ny);
                p->x = nx;
                p->y = ny;
                break;
            case 'F':
                nx = p->x - sin(p->a)*2;
                ny = p->y - cos(p->a)*2;
                drawLine(p->x, p->y, nx, ny);
                p->x = nx;
                p->y = ny;
                break;
            case '[':
                ptr = (Pos*)p->next;
                while(ptr) {
                    p = ptr;
                    ptr = (Pos*)p->next;
                }
                Pos* np  = malloc(sizeof(Pos));
                np->next = NULL;
                np->x = p0->x;
                np->y = p0->y;
                np->a = p0->a;
                p->next = np;
                break;
            case ']':
                ptr = p->next;
                while(ptr->next) {
                    p = ptr;
                    ptr = p->next;
                }

                p->next = NULL;
                p0->x = ptr->x;
                p0->y = ptr->y;
                p0->a = ptr->a;
                free(ptr);
                break;
            case '-':
                p->a += par.ang;
                break;
            case '+':
                p->a += -par.ang;
                break;
        }
    }
}

void ls(int width, int height, int steps) {
    Param par;
    par.ang = -25*M_PI/180;

    Pos p;
    p.x = width/2;
    p.y = height*3/4;
    p.a = 0;
    p.next = NULL;

    calc('X', &p, par, steps);
}


