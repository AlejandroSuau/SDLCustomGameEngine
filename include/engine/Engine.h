#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "SDLInitializer.h"
#include "Window.h"
#include "Color.h"
#include "Rectangle.h"
#include "IGame.h"

class Engine {
public:
    Engine(std::string window_title, int window_width, int window_height);
    
    void Run(IGame& game);
    void FixedUpdate();

    void DrawRectangle(const Rectangle& rect, const Color& color = {}, bool is_filled = false);
private:
    SDLInitializer sdl_initializer_;
    Window window_;
    bool is_running_;

    const float kFixedUpdateInterval = 0.016f;
    Uint64 last_fixed_update_;

    IGame* game_;

    void HandleEvents();
    void HandleMouseEvents(const SDL_Event& event);
    void HandleKeyboardEvents(const SDL_Event& event);
};
