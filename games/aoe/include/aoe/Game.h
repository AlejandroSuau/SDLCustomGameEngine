#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "GameMap.h"
#include "Unit.h"
#include "UnitMover.h"

class SDLInitializer {
public:
    SDLInitializer() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to init SDL -> " << SDL_GetError() << "\n";
            throw std::runtime_error("Failed to init SDL -> " + std::string(SDL_GetError()));
        }
    }
    ~SDLInitializer() { SDL_Quit(); }
};

/*class SDLImageInitializer {
public:
    SDLImageInitializer() {
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cerr << "Failed to init SDL_image -> " << SDL_GetError() << "\n";
            throw std::runtime_error("Fck");
        }
    }
    ~SDLImageInitializer() { IMG_Quit(); }
};*/

class SDLTTFInitializer {
public:
    SDLTTFInitializer() {
        if (TTF_Init() == -1) {
            std::cerr << "Failed to init SDL_ttf -> " << TTF_GetError() << "\n";
            throw std::runtime_error("Failed to init SDL_ttf -> " + std::string(TTF_GetError()));
        }
    }
    ~SDLTTFInitializer() { TTF_Quit(); }
};

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    std::unique_ptr<SDLInitializer> sdl_initializer_;
    //std::unique_ptr<SDLImageInitializer> sdl_img_initializer_;
    std::unique_ptr<SDLTTFInitializer> sdl_ttf_initializer_;

    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window_;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer_;
    bool is_running_;
    
    struct {
        bool is_button_down_ {false};
        bool did_move_ {false};
        
        float first_button_down_x_ {0.f};
        float first_button_down_y_ {0.f};
        
        float current_button_down_x_ {0.f};
        float current_button_down_y_ {0.f};
        SDL_Rect rect_;
    } left_button_data_;

    GameMap map_;
    UnitMover unit_mover_;
    std::vector<std::unique_ptr<Unit>> units_;

    TTF_Font* font_;

    void Init();
    void Update();
    void Render();
    void HandleEvents();
};
