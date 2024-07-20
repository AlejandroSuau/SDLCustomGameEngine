#include "fireworks/Particle.h"

#include "engine/Color.h"

namespace {
    static const std::size_t kTrailLength = 15;
    static const float kFadeDuration = .5f;
    static const Color kColor{75, 200, 150, 255};
    static const Vec2 kGravity {0.f, 9.8f};
}

Particle::Particle(
    Engine& engine,
    Color color,
    Vec2 position,
    Vec2 velocity,
    float radius,
    bool has_fade_animation,
    bool is_trail_active,
    bool is_applying_gravity)
    : engine_(engine)
    , color_(color)
    , position_(position)
    , velocity_{velocity}
    , acceleration_{0.f, 0.f}
    , radius_(radius)
    , can_be_destroyed(false)
    , fade_animation_(
        has_fade_animation ? std::make_unique<FadeOutColorAnimation>(color_, kFadeDuration) : nullptr)
    , is_trail_active_(is_trail_active)
    , is_applying_gravity_(is_applying_gravity) {
    trail_positions_.reserve(kTrailLength);
}

void Particle::Update(float dt) {
    if (fade_animation_) {
        fade_animation_->Update(dt);
        can_be_destroyed = fade_animation_->DidFinish();
    } else {
        can_be_destroyed = (position_.y > engine_.GetFWindowHeight());
    }

    if (is_applying_gravity_) {
        ApplyForce(kGravity);
    }

    velocity_ += acceleration_;
    position_ += velocity_ * dt;
    acceleration_ *= 0.f;

    if (is_trail_active_) {
        trail_positions_.push_back(position_);
        if (trail_positions_.size() > kTrailLength) {
            trail_positions_.erase(trail_positions_.begin());
        }
    }
}

const Vec2& Particle::GetPosition() const {
    return position_;
}

const Vec2& Particle::GetVelocity() const {
    return velocity_;
}

void Particle::SetVelocity(Vec2 velocity) {
    velocity_ = velocity;
}

bool Particle::CanBeDestroyed() const {
    return can_be_destroyed;
}

void Particle::Render() {
    if (is_trail_active_) {
        RenderTrail();
    }
    engine_.DrawCircle({radius_, position_}, color_);
}

void Particle::RenderTrail() {
    for (std::size_t i = 0; i < trail_positions_.size(); ++i) {
        Color trail_color = color_;
        trail_color.a = static_cast<Uint8>(color_.a * i / kTrailLength);
        engine_.DrawCircle({radius_, trail_positions_[i]}, trail_color);
    }
}

void Particle::ApplyForce(Vec2 force) {
    acceleration_ += force;
}
