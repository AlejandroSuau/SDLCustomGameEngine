#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>

class Window {
public:
    Window(std::string title, int width, int height);
    void Show();

    SDL_Window* GetWindowPtr();
    SDL_Renderer* GetRendererPtr();

private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> SDL_window_;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> SDL_renderer_;
};
