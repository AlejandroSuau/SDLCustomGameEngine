#pragma once

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Grid.h"

class SparkPropagation : public IGame {
public:
    SparkPropagation();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void UglyDraw();

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Grid grid_;
    CountdownTimer grid_tick_timer_;
};