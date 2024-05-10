#pragma once

#include "engine/IGame.h"
#include "engine/Engine.h"

#include "Grid.h"

class FallingSandGame : public IGame {
public:
    FallingSandGame();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Grid grid_;
};
