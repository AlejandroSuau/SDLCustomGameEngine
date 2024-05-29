#include "flappy_bird/include/Pipe.h"

#include <iostream>

namespace {
    static const float kVelocity = 100.f; // UnitsPerSecond
    static const Color kColor {100, 163, 119, 255};
}

const float Pipe::kWidth = 100.f;

Pipe::Pipe(Engine& engine, Vec2 position, float height)
    : engine_(engine)
    , position_(position)
    , dimension_(kWidth, height) {}

Pipe::Pipe(Engine& engine, Vec2 position, Vec2 dimension)
    : engine_(engine)
    , position_(position)
    , dimension_(dimension) {}

Rectangle Pipe::GetRectangle() const {
    return {position_.x, position_.y, dimension_.x, dimension_.y};
}

bool Pipe::CanBeDestroyed() const {
    return ((position_.x + dimension_.x) <= 0);
}

void Pipe::Update(float dt) {
    position_.x -= kVelocity * dt;
}

void Pipe::Render() {
    engine_.DrawRectangle({position_.x, position_.y, dimension_.x, dimension_.y}, kColor, true);
}