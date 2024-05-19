#include "falling_sand/include/FallingSandGame.h"

#include <iostream>

FallingSandGame::FallingSandGame() 
    : engine_("Falling Sand Game", 800, 600)
    , grid_(engine_, 800, 600)
    , particle_placer_(engine_, grid_, active_particle_manager_)
    , grid_tick_timer_(.05f) {}

void FallingSandGame::Start() {
    engine_.Run(*this);
}

void FallingSandGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    particle_placer_.OnMouseEvent(event_type, x, y);
}

void FallingSandGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE) {
        grid_.ClearAllParticles();
    } else if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_1) {
        grid_tick_timer_.AddSecondsToFinish(0.005f);
        std::cout << "\nSeconds updated: " << grid_tick_timer_.GetSecondsToFinish() << "ms";
    } else if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_2) {
        grid_tick_timer_.SubtractSecondsToFinish(0.005f);
        std::cout << "\nseconds updated: " << grid_tick_timer_.GetSecondsToFinish() << "ms";
    } else {
        active_particle_manager_.OnKeyboardEvent(event_type, scancode);
    }
}

void FallingSandGame::Update(float dt) {
    grid_tick_timer_.Update(dt);
    if (!grid_tick_timer_.DidFinish()) return;

    grid_tick_timer_.Reset();
    grid_.UpdateCells(dt);
}

void FallingSandGame::Render() {
    grid_.RenderCells();
}
