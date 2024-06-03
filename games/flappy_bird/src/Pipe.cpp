#include "flappy_bird/include/Pipe.h"

#include <iostream>

namespace {
    static const float kVelocity = 100.f; // UnitsPerSecond
    static const Color kColor {100, 163, 119, 255};
}

const float Pipe::kWidth = 50.f;

Pipe::Pipe(Engine& engine, Vec2 position, float height)
    : engine_(engine)
    , position_(position)
    , dimension_(kWidth, height)
    , vertical_alignment_((position_.y == 0.f) ? EVerticalAlignment::TOP : EVerticalAlignment::BOTTOM)
    , current_status_(EStatus::DEFAULT) {}

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
    
    if (IsFlatting()) {
        const float flatting_velocity = 10.f;
        if (vertical_alignment_ == EVerticalAlignment::TOP) {
            dimension_.y -= flatting_velocity * dt;
            if (dimension_.y <= 0.f) dimension_.y = 0.f;
        } else {
            float new_y = flatting_velocity * dt;
            dimension_.y -= (new_y);
            if (dimension_.y <= 0.f) {
                dimension_.y = 0.f;
            } else {
                position_.y += (new_y);
            }
        }
    }
}

void Pipe::SetStatusFlatting() {
    current_status_ = EStatus::FLATTING;
}

bool Pipe::IsFlatting() const {
    return (current_status_ == EStatus::FLATTING);
}

void Pipe::Render() {
    engine_.DrawRectangle({position_.x, position_.y, dimension_.x, dimension_.y}, kColor, true);
}