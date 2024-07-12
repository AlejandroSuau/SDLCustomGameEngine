#include "flappy_bird/include/Bird.h"

#include "flappy_bird/include/Constants.h"

#include "engine/Rectangle.h"

#include <cmath>

Bird::Bird(Engine& engine, float x, float y)
    : engine_(engine)
    , current_state_(EBirdState::STANDING)
    , starting_position_{x, y}
    , hit_box_(x, y, kBirdWidth, kBirdHeight)
    , velocity_(0.f)
    , oscillation_time_(0.f)
    , flying_animation_timer_(0.1f)
    , current_fly_texture_index_(0) {
    LoadTextures();
}

void Bird::LoadTextures() {
    flying_textures_[0] = engine_.LoadTexture(kAssetsFolder + "yellowbird-upflap.png");
    flying_textures_[1] = engine_.LoadTexture(kAssetsFolder + "yellowbird-midflap.png");
    flying_textures_[2] = engine_.LoadTexture(kAssetsFolder + "yellowbird-downflap.png");
}

void Bird::Jump() {
    velocity_ = kBirdJumpForce;
    current_state_ = EBirdState::FLYING;
}

void Bird::Update(float dt) {
    switch(current_state_) {
        case EBirdState::DYING:
            UpdateFallingPosition(dt);
        break;
        case EBirdState::FLYING:
            UpdateAnimationFlying(dt);
            UpdateFallingPosition(dt);
        break;
        case EBirdState::STANDING:
            UpdateAnimationFlying(dt);
            UpdateAnimationStanding(dt);
        break;
    }
}

void Bird::UpdateFallingPosition(float dt) {
    velocity_ += kBirdGravity * dt;
    hit_box_.y += velocity_ * dt;
}

void Bird::UpdateAnimationFlying(float dt) {
    flying_animation_timer_.Update(dt);
    if (!flying_animation_timer_.DidFinish()) return;
    
    current_fly_texture_index_ = ++current_fly_texture_index_ % flying_textures_.size();
    flying_animation_timer_.Reset();
}

void Bird::UpdateAnimationStanding(float dt) {
    oscillation_time_ += dt;
    hit_box_.y = starting_position_.y + kBirdFloatingAmplitude * std::sin(kBirdFloatingVelocity * oscillation_time_);
}

void Bird::OnCollisionWithFloor(float floor_y_position) {
    hit_box_.y = floor_y_position - kBirdHeight;
    current_state_ = EBirdState::DEAD;
}

void Bird::OnCollisionWithPipe() {
    current_state_ = EBirdState::DYING;
}

void Bird::Render() {
    if (DEBUG) {
        engine_.DrawRectangle(
            {hit_box_.x, hit_box_.y, hit_box_.w, hit_box_.h},
            kBirdHitBoxColor,
            false);
    } else {
        engine_.RenderTexture(
            flying_textures_[current_fly_texture_index_],
            {hit_box_.x, hit_box_.y, hit_box_.w, hit_box_.h});
    }
}

const Rectangle& Bird::GetHitBox() const {
    return hit_box_;
}

void Bird::Reset() {
    hit_box_.x = starting_position_.x;
    hit_box_.y = starting_position_.y;
    current_state_ = EBirdState::STANDING;
}
