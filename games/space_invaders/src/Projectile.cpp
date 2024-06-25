#include "space_invaders/include/Projectile.h"

#include "space_invaders/include/Constants.h"

Projectile::Projectile(Engine& engine, EProjectileDirection direction, float x, float y) 
    : engine_(engine)
    , current_direction_(direction)
    , rect_(x, y, kProjectileWidth, kProjectileHeight) {}

void Projectile::Update(float dt) {
    auto dy = kProjectileVelocity * dt;
    dy *= (current_direction_ == EProjectileDirection::UP) ? -1 : 1; 
    rect_.y += dy;
}

void Projectile::Render() {
    engine_.DrawRectangle(rect_);
}

bool Projectile::IsInsideBounds() const {
    return (rect_.y + rect_.h >= 0 && rect_.y < engine_.GetWindowHeight());
}

bool Projectile::CollidesWith(const Rectangle& other) const {
    return (rect_.CollidesWith(other));
}

const Rectangle& Projectile::GetRectangle() const {
    return rect_;
}
