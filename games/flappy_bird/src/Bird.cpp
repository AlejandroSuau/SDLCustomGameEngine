#include "flappy_bird/include/Bird.h"

#include "engine/Rectangle.h"

#include <cmath>

namespace {
    static const float kBirdWidth = 34.f;
    static const float kBirdHeight = 24.f;

    static const float kVelocity = 400.f;
    static const float kGravity = 1000.f;
    static const float kJumpForce = -300.f;

    static const float kFloatingAmplitude = 25.f;
    static const float kFloatingVelocity = 5.f;
}

Bird::Bird(Engine& engine, float x, float y)
    : engine_(engine)
    , current_state_(EBirdState::STANDING)
    , starting_position_(x, y)
    , position_(x, y)
    , dimension_(kBirdWidth, kBirdHeight)
    , velocity_(0.f)
    , oscillation_time_(0.f)
    , flying_animation_timer_(0.1f)
    , current_fly_texture_index_(0) {
    LoadTextures();
}

void Bird::LoadTextures() {
    flying_textures_[0] = engine_.LoadTexture("assets/flappy_bird/yellowbird-upflap.png");
    flying_textures_[1] = engine_.LoadTexture("assets/flappy_bird/yellowbird-midflap.png");
    flying_textures_[2] = engine_.LoadTexture("assets/flappy_bird/yellowbird-downflap.png");
}

void Bird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bool space_key_pressed = (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE);
    if (!space_key_pressed || IsDying() || IsDead()) return;

    velocity_ = kJumpForce;
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
        default:
        break;
    }
}

void Bird::Reset() {
    position_ = starting_position_;
    current_state_ = EBirdState::STANDING;
}

void Bird::UpdateFallingPosition(float dt) {
    velocity_ += kGravity * dt;
    position_.y += velocity_ * dt;
}

void Bird::UpdateAnimationFlying(float dt) {
    flying_animation_timer_.Update(dt);
    if (!flying_animation_timer_.DidFinish()) return;
    
    current_fly_texture_index_ = ++current_fly_texture_index_ % flying_textures_.size();
    flying_animation_timer_.Reset();
}

void Bird::UpdateAnimationStanding(float dt) {
    oscillation_time_ += dt;
    position_.y = starting_position_.y + kFloatingAmplitude * std::sin(kFloatingVelocity * oscillation_time_);
}

void Bird::OnCollisionWithFloor(float floor_y_position) {
    position_.y = floor_y_position - kBirdHeight;
    current_state_ = EBirdState::DEAD;
}

void Bird::OnCollisionWithPipe() {
    current_state_ = EBirdState::DYING;
}

void Bird::SetStateDying() {
    current_state_ = EBirdState::DYING;
}

void Bird::SetStateDead() {
    current_state_ = EBirdState::DEAD;
}

void Bird::Render() {
    engine_.DrawRectangle(
        {position_.x, position_.y, dimension_.x, dimension_.y},
        {255, 255, 255, 255},
        false);
    
    engine_.RenderTexture(
        flying_textures_[current_fly_texture_index_],
        {position_.x, position_.y, dimension_.x, dimension_.y});
}

bool Bird::CollidesWith(Pipe& pipe) const {
    Rectangle bird_r {position_.x, position_.y, dimension_.x, dimension_.y};
    const auto pipe_r = pipe.GetRectangle();
    return bird_r.CollidesWith(pipe_r);
}

Rectangle Bird::GetRectangle() const {
    return {position_.x, position_.y, dimension_.x, dimension_.y};
}

const Vec2& Bird::GetDimension() const {
    return dimension_;
}

bool Bird::IsFlying() const {
    return (current_state_ == EBirdState::FLYING);
}

bool Bird::IsStanding() const {
    return (current_state_ == EBirdState::STANDING);
}

bool Bird::IsDead() const {
    return (current_state_ == EBirdState::DEAD);
}

bool Bird::IsDying() const {
    return (current_state_ == EBirdState::DYING);
}

void Bird::SetStateFlying() {
    current_state_ = EBirdState::FLYING;
}

