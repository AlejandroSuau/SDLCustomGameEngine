#include "doodle_jump/include/Player.h"

namespace {
    static const float kWidth = 20.f;
    static const float kHeight = 20.f;
    static const float kGravity = 750.f;
    static const float kJumpForce = -500.f;
    static const float kHorizontalVelocity = 300.f;

    static const unsigned int kMask = 1;
    static const unsigned int kLayer = 2;

}

Player::Player(Engine& engine) 
    : engine_(engine)
    , velocity_{0.f, 0.f}
    , rect_(engine_.GetFWindowWidth() * 0.5f, engine_.GetFWindowHeight() * 0.5f, kWidth, kHeight)
    , state_(EPlayerState::FALLING)
    , direction_(EPlayerDirection::NONE) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

Player::~Player() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

void Player::Update(float dt) {
    velocity_.y += kGravity * dt;
    rect_.y += velocity_.y * dt;
    rect_.x += velocity_.x * dt;
    state_ = (velocity_.y > 0.f) ? EPlayerState::FALLING : EPlayerState::JUMPING;
}

void Player::Render() {
    engine_.DrawRectangle(rect_, {255, 255, 255, 255}, true);
}

void Player::Jump(float jump_force) {
    velocity_.y = jump_force;
}


void Player::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    const bool is_key_down = (event_type == EKeyEventType::KEY_DOWN);
    const bool is_key_up = (event_type == EKeyEventType::KEY_UP);

    switch(scancode) {
        case SDL_SCANCODE_RIGHT:
            if (is_key_down) {
                direction_ = EPlayerDirection::RIGHT;
                velocity_.x = kHorizontalVelocity;
            } else if (is_key_up && direction_ == EPlayerDirection::RIGHT) {
                direction_ = EPlayerDirection::NONE;
                velocity_.x = 0.f;
            }
        break;
        case SDL_SCANCODE_LEFT:
            if (is_key_down) {
                direction_ = EPlayerDirection::LEFT;
                velocity_.x = -kHorizontalVelocity;
            } else if (is_key_up && direction_ == EPlayerDirection::LEFT) {
                direction_ = EPlayerDirection::NONE;
                velocity_.x = 0;
            }
        break;
        case SDL_SCANCODE_SPACE: 
            Jump(kJumpForce);
        break;
    }
}

bool Player::IsJumping() const {
    return (state_ == EPlayerState::JUMPING);
}

bool Player::IsFalling() const {
    return (state_ == EPlayerState::FALLING);
}

Vec2 Player::GetPosition() const {
    return {rect_.x, rect_.y};
}

const Rectangle& Player::GetBoundingBox() const {
    return rect_;
}

void Player::OnCollision(ICollidable& other) {
    if (state_ == EPlayerState::FALLING) {
        Jump(kJumpForce);
    }
}

unsigned int Player::GetLayer() const {
    return kLayer;
}

unsigned int Player::GetMask() const {
    return kMask;
}
