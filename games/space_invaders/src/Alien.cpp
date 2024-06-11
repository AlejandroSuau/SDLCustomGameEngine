#include "space_invaders/include/Alien.h"

#include "space_invaders/include/Constants.h"

Alien::Alien(Engine& engine, Vec2 position) 
    : engine_(engine)
    , rect_(position.x, position.y, kAlienWidth, kAlienHeight)
    , lifes_(1) {}

void Alien::MovementStep(EAlienMovementDirection movement_direction) {
    switch(movement_direction) {
        case EAlienMovementDirection::RIGHT:
            rect_.x += kAlienMovementStepX;
            break;
        case EAlienMovementDirection::LEFT:
            rect_.x -= kAlienMovementStepX;
            break;
        case EAlienMovementDirection::DOWN:
            rect_.y += kAlienMovementStepY;
            break;
    }
}

void Alien::Render() {
    engine_.DrawRectangle(rect_);
}

void Alien::Hit() {
    --lifes_;
}

const Rectangle& Alien::GetRectangle() const {
    return rect_;
}

void Alien::SetPosition(Vec2 position) {
    rect_.x = position.x;
    rect_.y = position.y;
}

Vec2 Alien::GetPosition() const {
    return {rect_.x, rect_.y};
}

bool Alien::IsAlive() const {
    return (lifes_ > 0);
}
