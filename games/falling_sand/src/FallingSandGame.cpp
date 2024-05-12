#include "falling_sand/include/FallingSandGame.h"

FallingSandGame::FallingSandGame() 
    : engine_("Falling Sand Game", 800, 600)
    , grid_(engine_, 800, 600)
    , particle_placer_(grid_, active_particle_manager_) {}

void FallingSandGame::Start() {
    engine_.Run(*this);
}

void FallingSandGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    particle_placer_.OnMouseEvent(event_type, x, y);
}

void FallingSandGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE) {
        grid_.ClearAllParticles();
    } else {
        active_particle_manager_.OnKeyboardEvent(event_type, scancode);
    }
}

void FallingSandGame::Update(float dt) {
    grid_.UpdateCells(dt);
}

void FallingSandGame::Render() {
    grid_.RenderCells();
}
