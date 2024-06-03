#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SDLInitializer.h"
#include "SDLImageInitializer.h"
#include "Window.h"
#include "Color.h"
#include "Rectangle.h"
#include "IGame.h"
#include "RandomGenerator.h"
#include "TextureManager.h"

class Engine {
public:
    Engine(std::string window_title, int window_width, int window_height);
    
    void Run(IGame& game);

    void RenderTexture(SDL_Texture* texture, const Rectangle& source_rect, const Rectangle& destination_rect);
    void DrawRectangle(const Rectangle& rect, const Color& color = {}, bool is_filled = false);
    SDL_Texture* LoadTexture(const std::string& file_path);

    RandomGenerator& GetRandomGenerator();
    int GetWindowWidth() const;
    int GetWindowHeight() const;

private:
    SDLInitializer sdl_initializer_;
    SDLImageInitializer sdl_image_initializer_;
    Window window_;
    RandomGenerator random_generator_;
    TextureManager texture_manager_;
    bool is_running_;

    const float kFixedUpdateInterval = 0.016f;
    Uint64 last_fixed_update_;

    IGame* game_;

    void HandleEvents();
    void HandleMouseEvents(const SDL_Event& event);
    void HandleKeyboardEvents(const SDL_Event& event);
};
