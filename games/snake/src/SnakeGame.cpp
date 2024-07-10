#include "snake/include/SnakeGame.h"

#include "engine/Rectangle.h"

SnakeGame::SnakeGame() 
    : engine_("Snake", 800, 600)
    , snake_(engine_)
    , food_factory_(engine_, snake_)
    , food_(food_factory_.CreateFood())
    , boundaries_{{
        {engine_, snake_, {0.f, 0.f, static_cast<float>(engine_.GetWindowWidth()), 1.f}},
        {engine_, snake_, {0.f, 0.f, 1.f, static_cast<float>(engine_.GetWindowHeight())}},
        {engine_, snake_, {static_cast<float>(engine_.GetWindowWidth()) - 1.f, 0.f, 1.f, static_cast<float>(engine_.GetWindowHeight())}},
        {engine_, snake_, {0.f, static_cast<float>(engine_.GetWindowHeight()) - 1.f, static_cast<float>(engine_.GetWindowWidth()), 1.f}}
    }} {}

void SnakeGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void SnakeGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (!snake_.IsAlive()) {
        if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE) {
            snake_.Reset();
        } 
    }
    snake_.OnKeyboardEvent(event_type, scancode);
}

void SnakeGame::Start() {
    engine_.Run(*this);
}

void SnakeGame::Update(float dt) {
    if (food_ && food_->IsMarkedForDestroy()) {
        food_ = food_factory_.CreateFood();
    }

    if (snake_.IsAlive()) {
        snake_.Update(dt);
    }
}

void SnakeGame::Render() {
    snake_.Render();
    
    for (auto& boundary : boundaries_) {
        boundary.Render();
    }

    if (food_) {
        food_->Render();
    }
}

