#include "fireworks/FireworksGame.h"

#include <iostream>

FireworksGame::FireworksGame() 
    : engine_("Fireworks", 700, 800)
    , firework_(engine_) {}
    
void FireworksGame::Start() {
    engine_.Run(*this);
}

void FireworksGame::Update(float dt) {
    firework_.Update(dt);
}

void FireworksGame::Render() {
    firework_.Render();
}

void FireworksGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {

}

void FireworksGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {

}
