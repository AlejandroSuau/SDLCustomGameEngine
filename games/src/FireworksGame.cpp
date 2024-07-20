#include "fireworks/FireworksGame.h"

#include <iostream>

FireworksGame::FireworksGame() 
    : engine_("Fireworks", 700, 800) {}
    
void FireworksGame::Start() {
    engine_.Run(*this);
}

void FireworksGame::Update(float dt) {
    if (engine_.GetRandomGenerator().Generate(0.f, 1.f) < 0.01f) {
        fireworks_.emplace_back(std::make_unique<Firework>(engine_));
    }

    for (auto& firework : fireworks_) {
        firework->Update(dt);
    }

    ClearDestroyableFireworks();
}

void FireworksGame::ClearDestroyableFireworks() {
    fireworks_.erase(
        std::remove_if(fireworks_.begin(), fireworks_.end(), [](const auto& f) { return f->CanBeDestroyed(); }),
        fireworks_.end()
    );
}

void FireworksGame::Render() {
    for (auto& firework : fireworks_) {
        firework->Render();
    }
}

void FireworksGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {

}

void FireworksGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {

}
