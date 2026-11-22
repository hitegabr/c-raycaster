//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	SDL and window/input stuff.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include "raycaster.h"
#include "map.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycaster", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          640, 480, 
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initWallColors();

    int running = 1;
    SDL_Event e;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Time/tick stuff.
        Uint32 currentTime = SDL_GetTicks();
        double frameTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        updatePlayer(frameTime);

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        castRays(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
