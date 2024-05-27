#include "flappy_bird/include/FlappyBird.h"

#include <iostream>

FlappyBird::FlappyBird() 
    : engine_("Flappy Bird", 800, 600)
    , bird_(engine_) {}

void FlappyBird::Start() {
    engine_.Run(*this);
}

void FlappyBird::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bird_.OnKeyboardEvent(event_type, scancode);
}

void FlappyBird::Update(float dt) {
    bird_.Update(dt);
}

void FlappyBird::Render() {
    bird_.Render();
}
