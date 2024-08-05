#include "fireworks/Firework.h"

#include "fireworks/shape_generator/ShapeGenerator.h"
#include "fireworks/shape_generator/Shapes.h"

#include <array>
#include <iostream>

namespace {
    static const Vec2 kSize {100.f, 20.f};
}

Firework::Firework(Engine& engine)
    : engine_(engine)
    , pos_(engine_.GetFWindowWidth() * 0.5f, engine_.GetFWindowHeight() * 0.5f)
    , vel_(0.f, -50.f)
    , acc_()
    , angle_(vel_.Heading()) {}

void Firework::Update(float dt) {
    acc_ *= 0.f;
    vel_ += acc_;
    pos_ += vel_ * dt;
    direction_ += dt;
    angle_ = vel_.Heading() + static_cast<float>(M_PI) / 90.f;
}

void Firework::Render() {
    engine_.DrawRectangle({pos_.x, pos_.y, kSize.x, kSize.y}, angle_);    
    
    Vec2 center {pos_.x + kSize.y * 0.5f, pos_.y + kSize.x / 2.f};
    Vec2 direction {center.x + 50.f * cos(angle_), center.y + 50.f * sin(angle_)};
    engine_.DrawLine(center, direction, {255, 100, 100, 255});
}