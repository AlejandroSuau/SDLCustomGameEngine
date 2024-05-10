#include "falling_sand/include/FallingSandGame.h"

FallingSandGame::FallingSandGame() 
    : engine_("Falling Sand Game", 800, 600)
    , grid_(engine_, 800, 600) {}

void FallingSandGame::Start() {
    engine_.Run(*this);
}

void FallingSandGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {

}

void FallingSandGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {

}

void FallingSandGame::Update(float dt) {

}

void FallingSandGame::Render() {
    grid_.RenderCells();
}
