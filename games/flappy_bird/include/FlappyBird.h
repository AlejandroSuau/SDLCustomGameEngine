#pragma once

#include "engine/IGame.h"
#include "engine/Engine.h"

#include "Bird.h"

class FlappyBird : public IGame {
public:
    FlappyBird();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Bird bird_;
};