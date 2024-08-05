#pragma once

#include "engine/Engine.h"

#include "fireworks/Firework.h"

#include <vector>
#include <memory>

class FireworksGame : public IGame {
public:
    FireworksGame();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Firework firework_;
};
