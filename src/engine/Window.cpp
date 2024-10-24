#include "engine/Window.h"

#include <stdexcept>

Window::Window(std::string title, int width, int height)
    : SDL_window_(
        SDL_CreateWindow(title.c_str(),
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         width,
                         height,
                         0),
        SDL_DestroyWindow)
    , SDL_renderer_(
        SDL_CreateRenderer(SDL_window_.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer) {
    if (!SDL_window_ || !SDL_renderer_) {
        throw std::runtime_error(
            std::string("Error creating window: ") + SDL_GetError());
    }
}

SDL_Window* Window::GetWindowPtr() {
    return SDL_window_.get();
}
SDL_Renderer* Window::GetRendererPtr() {
    return SDL_renderer_.get();
}

void Window::Show() {
    SDL_ShowWindow(SDL_window_.get());
}
