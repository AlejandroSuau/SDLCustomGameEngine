#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "GameMap.h"
#include "Unit.h"
#include "UnitMover.h"

class Game {
public:
    Game();

    void Run();

private:
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

    void Init();
    void Update();
    void Render();
    void HandleEvents();
};
