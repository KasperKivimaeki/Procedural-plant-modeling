#include "ls.h"
#include "sdl.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

struct pos {
    void* next;
    int x;
    int y;
    double ang;
};

#define Pos struct pos

float size(float real, float c) {
    return sqrt(real*real + c*c);
}

int match(char c) {
    switch(c) {
        case '0':
            return 1;
        case '1':
            return 0;
        default:
            return -1;
    }
}

void drawLine(int x0, int y0, int x1, int y1) {
    SDL_SetRenderDrawColor(app.renderer, 0, 0xff, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(app.renderer, x0, y0, x1, y1);
}

void calc(int w, char c, Pos* p, int* x, int* y, double* ang, int d) {
    if(*y < 0) {
        return;
    }
    int ruleS[2] = {2, 5};
    char* words[] = {"11", "1[0]0"};

    int it = match(c);

    if(it >= 0 && d > 0) {
        for(int i = 0; i < ruleS[it]; i++) {
            calc(w, words[it][i], p, x, y, ang, d - 1);
        }
    } else {
        Pos* ptr = NULL;
        int nx, ny;
        switch(c) {
            case '0':
                nx = *x - sin(*ang)*2;
                ny = *y - cos(*ang)*2;
                drawLine(*x, *y, nx, ny);
                *x = nx;
                *y = ny;
                break;
            case '1':
                nx = *x - sin(*ang)*4;
                ny = *y - cos(*ang)*4;
                drawLine(*x, *y, nx, ny);
                *x = nx;
                *y = ny;
                break;
            case '[':
                ptr = (Pos*)p->next;
                while(ptr) {
                    p = ptr;
                    ptr = (Pos*)p->next;
                }
                struct pos* np  = malloc(sizeof(struct pos));
                np->next = NULL;
                np->x = *x;
                np->y = *y;
                np->ang = *ang;

                p->next = np;

                *ang += -45*M_PI/180;
                break;
            case ']':
                ptr = p->next;
                while(((struct pos*)ptr)->next) {
                    p = ptr;
                    ptr = ((struct pos*)p)->next;
                }

                p->next = NULL;
                *x = ((struct pos*)ptr)->x;
                *y = ((struct pos*)ptr)->y;
                *ang = ((struct pos*)ptr)->ang;

                *ang += 45*M_PI/180;

                free(ptr);
                break;
        }
    }
}

void ls(int width, int height, int steps) {
    int x = width/2;
    int y = height*3/4;
    double ang = 0;

    Pos *p = malloc(sizeof(struct pos));
    p->x = 0;
    p->y = 0;
    p->ang = 0;
    p->next = NULL;

    char axiom = '0';

    calc(width, axiom, p, &x, &y, &ang, steps);
}


