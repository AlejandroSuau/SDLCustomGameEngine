#include <SDL2/SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(0);

    SDL_Window* window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        500, 500,
        0);

    SDL_ShowWindow(window);

    bool is_running = true;
    while(is_running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            is_running = (event.type != SDL_QUIT);
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
