#pragma once

#include <string>

#include "SDLInitializer.h"
#include "Window.h"

class Engine {
public:
    Engine(std::string window_title, int window_width, int window_height);
    void Run();
private:
    SDLInitializer sdl_initializer_;
    Window window_;
    bool is_running_;

    void HandleEvents();
};
