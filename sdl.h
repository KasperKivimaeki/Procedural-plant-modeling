#ifndef SDL_H
#define SDL_H

#include <SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void prepareScene(int, const void*);
void presentScene();
void initSDL();

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *texture;
} App;

App app;

#endif
