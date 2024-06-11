#include "space_invaders/include/Projectile.h"

#include "space_invaders/include/Constants.h"

Projectile::Projectile(Engine& engine, float x, float y) 
    : engine_(engine)
    , rect_(x, y, kProjectileWidth, kProjectileHeight) {}

void Projectile::Update(float dt) {
    rect_.y -= kProjectileVelocity * dt;
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

