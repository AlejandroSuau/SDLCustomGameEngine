#include "space_invaders/include/Alien.h"

#include "space_invaders/include/Constants.h"

Alien::Alien(Engine& engine, Vec2 position, std::array<Rectangle, 2> source_rects) 
    : engine_(engine)
    , source_rects_(source_rects)
    , current_source_index_(0)
    , rect_(position.x, position.y, kAlienWidth, kAlienHeight)
    , lifes_(1) {
    LoadTextures();
}

void Alien::LoadTextures() {
    texture_atlas_ = engine_.LoadTexture("assets/space_invaders/SpaceInvaders.png");
}

void Alien::MovementStep(EAlienMovementDirection movement_direction) {
    current_source_index_ = ++current_source_index_ % source_rects_.size();

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
    engine_.RenderTexture(texture_atlas_, 
                          source_rects_[current_source_index_],
                          {rect_.x, rect_.y, kAlienWidth, kAlienHeight});
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
