#include "flappy_bird/include/Pipe.h"

#include <iostream>

namespace {
    static const float kMinimumHeight;
    static const Color kColor {100, 163, 119, 255};
}

const float Pipe::kMinimumHeight = 50.f;
const float Pipe::kWidth = 52.f;

Pipe::Pipe(Engine& engine, Vec2 position, float height)
    : engine_(engine)
    , position_(position)
    , dimension_(kWidth, height)
    , vertical_alignment_((position_.y == 0.f) ? EVerticalAlignment::TOP : EVerticalAlignment::BOTTOM) {
    LoadTexture();
}

Pipe::Pipe(Engine& engine, Vec2 position, Vec2 dimension)
    : engine_(engine)
    , position_(position)
    , dimension_(dimension) {
    LoadTexture();
}

void Pipe::LoadTexture() {
    texture_ = engine_.LoadTexture("assets/flappy_bird/pipe-green.png");
}

Rectangle Pipe::GetRectangle() const {
    return {position_.x, position_.y, dimension_.x, dimension_.y};
}

Vec2& Pipe::GetPosition() {
    return position_;
}

void Pipe::Render() {
    // engine_.DrawRectangle({position_.x, position_.y, dimension_.x, dimension_.y}, kColor, false);
    
    engine_.RenderTexture(
        texture_,
        {position_.x, position_.y, dimension_.x, dimension_.y},
        (vertical_alignment_ == EVerticalAlignment::TOP) ? 180 : 0);
}