#include "flappy_bird/include/Bird.h"

namespace {
    static const float kBirdWidth = 20.f;
    static const float kBirdHeight = 20.f;
    static const float kStartingX = 300.f;
    static const float kStartingY = 300.f;

    static const float kVelocity = 400.f;
    static const float kGravity = 1000.f;
    static const float kJumpForce = -300.f;
}

Bird::Bird(Engine& engine)
    : engine_(engine)
    , current_state_(EBirdState::NONE)
    , position_(kStartingX, kStartingY)
    , dimension_(kBirdWidth, kBirdHeight)
    , velocity_(0.f) {}

void Bird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bool space_key_pressed = (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE);
    if (!space_key_pressed || IsFlying()) return;

    velocity_ = kJumpForce;
    current_state_ = EBirdState::FLYING;
}

void Bird::Update(float dt) {
    velocity_ += kGravity * dt;    
    position_.y += velocity_ * dt;

    if (velocity_ > 0) {
        current_state_ = EBirdState::FALLING;
    } else {
        current_state_ = EBirdState::FLYING;
    }
}

void Bird::Render() {
    engine_.DrawRectangle(
        {position_.x, position_.y, dimension_.x, dimension_.y},
        {255, 255, 255, 255},
        false);
}

bool Bird::IsFlying() const {
    return (current_state_ == EBirdState::FLYING);
}

bool Bird::IsFalling() const {
    return (current_state_ == EBirdState::FALLING);
}

void Bird::SetStateFalling() {
    current_state_ = EBirdState::FALLING;
}

void Bird::SetStateFlying() {
    current_state_ = EBirdState::FLYING;
}

