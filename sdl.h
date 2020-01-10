#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void prepareScene(const void*);
void presentScene();
void initSDL();

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *texture;
} App;

App app;

#endif
