#include "engine/Engine.h"

Engine::Engine(std::string window_title, int window_width, int window_height)
    : sdl_initializer_(0)
    , window_(window_title, window_width, window_height)
    , is_running_(false) {

}

void Engine::Run() {
    is_running_ = true;
    
    window_.Show();
    while(is_running_) {
        SDL_RenderClear(window_.GetRendererPtr());

        HandleEvents();

        // Draw game / rectangle
        SDL_SetRenderDrawColor(window_.GetRendererPtr(), 255, 255, 255, 255);
        SDL_Rect r;
        r.x = 5;
        r.y = 5;
        r.w = 20;
        r.h = 20;
        SDL_RenderDrawRect(window_.GetRendererPtr(), &r);

        SDL_SetRenderDrawColor(window_.GetRendererPtr(), 0, 0, 0, 255);
        SDL_RenderPresent(window_.GetRendererPtr());
    }
}

void Engine::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running_ = false;
        }
    }
}
