#include "flappy_bird/include/Bird.h"

namespace {
    static const float kBirdWidth = 20.f;
    static const float kBirdHeight = 20.f;
    static const float kStartingX = 300.f;
    static const float kStartingY = 300.f;
}

Bird::Bird(Engine& engine)
    : engine_(engine)
    , position_(kStartingX, kStartingY)
    , dimension_(kBirdWidth, kBirdHeight)
    , current_state_(EBirdState::NONE) {}

void Bird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (scancode == SDL_SCANCODE_SPACE) {
        current_state_ = (event_type == EKeyEventType::KEY_DOWN) ? EBirdState::FLYING : EBirdState::FALLING;
    }
}

void Bird::Update(float dt) {
    switch(current_state_) {
        case EBirdState::FALLING:
            position_.y += (400.f * dt);
            break;
        case EBirdState::FLYING:
            position_.y -= (400.f * dt);
            break;
        case EBirdState::NONE:
        default:
            break;
    }
}

void Bird::Render() {
    engine_.DrawRectangle(
        {position_.x, position_.y, dimension_.x, dimension_.y},
        {255, 255, 255, 255},
        false);
}

bool Bird::IsFlying() const {
    return false;
}

bool Bird::IsFalling() const {
    return false;
}

void Bird::SetStateFalling() {
    current_state_ = EBirdState::FALLING;
}

void Bird::SetStateFlying() {
    current_state_ = EBirdState::FLYING;
}

