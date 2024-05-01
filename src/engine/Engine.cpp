#include "engine/Engine.h"

Engine::Engine(std::string window_title, int window_width, int window_height)
    : sdl_initializer_(0)
    , window_(window_title, window_width, window_height)
    , is_running_(false)
    , game_(nullptr)
    , last_fixed_update_(SDL_GetTicks64()) {

}

void Engine::Run(IGame& game) {
    game_ = &game;
    is_running_ = true;
    
    window_.Show();
    while(is_running_) {
        SDL_RenderClear(window_.GetRendererPtr());

        HandleEvents();

        FixedUpdate();
        game_->Render();

        SDL_SetRenderDrawColor(window_.GetRendererPtr(), 0, 0, 0, 255);
        SDL_RenderPresent(window_.GetRendererPtr());
    }
}

void Engine::FixedUpdate() {
    const auto current_time = SDL_GetTicks64();
    const float dt_in_seconds = static_cast<float>(current_time - last_fixed_update_) / 1000.f;
    if (dt_in_seconds >= kFixedUpdateInterval) {
        game_->Update(dt_in_seconds);
        last_fixed_update_ = current_time;
    }
}

void Engine::DrawRectangle(const Rectangle& rect, const Color& color) {
    SDL_SetRenderDrawColor(window_.GetRendererPtr(), color.r, color.g, color.b, color.a);
    SDL_Rect r {
        static_cast<int>(rect.x),
        static_cast<int>(rect.y),
        static_cast<int>(rect.w),
        static_cast<int>(rect.h)};
    SDL_RenderDrawRect(window_.GetRendererPtr(), &r);
}

void Engine::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running_ = false;
        }
    }
}
