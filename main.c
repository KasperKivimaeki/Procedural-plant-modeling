#include "sdl.h"
#include "ls.h"
#include <stdio.h>

float sx1;
float sy1;

int user_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEBUTTONDOWN:
                printf("(x, y) (%d, %d)\n", event.button.x, event.button.y);
                return 2;
                break;
            default:
                break;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(app));

    initSDL();

    int step = 0;
    int frame = 0;

    void* buffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
    ls(SCREEN_WIDTH, SCREEN_HEIGHT, step);
    prepareScene(frame, buffer);
    presentScene();

    int input = user_input();
    while(input) {
        SDL_Delay(16);
        frame += 1;

        if(input == 2) {
            step++;
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(app.renderer);

            ls(SCREEN_WIDTH, SCREEN_HEIGHT, step);
            //presentScene();
        }
        SDL_RenderPresent(app.renderer);

        input = user_input();
    }

    free(buffer);
    printf("Hello\n");
    return 0;
}
