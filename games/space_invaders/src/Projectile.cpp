#include "space_invaders/include/Projectile.h"

#include "space_invaders/include/Constants.h"
#include "space_invaders/include/Alien.h"

Projectile::Projectile(
    Engine& engine,
    EProjectileDirection direction,
    float x,
    float y,
    unsigned int layer,
    unsigned int mask) 
    : engine_(engine)
    , current_direction_(direction)
    , layer_(layer)
    , mask_(mask)
    , rect_(x, y, kProjectileWidth, kProjectileHeight)
    , is_marked_for_destroy_(false) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

Projectile::~Projectile() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

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

void Projectile::MarkForDestroy() {
    is_marked_for_destroy_ = true;
}

bool Projectile::IsMarkedForDestroy() const {
    return is_marked_for_destroy_;
}

const Rectangle& Projectile::GetBoundingBox() const {
    return rect_;
}

void Projectile::OnCollision(ICollidable& other) {
    MarkForDestroy();
}

unsigned int Projectile::GetLayer() const {
    return layer_;
}

unsigned int Projectile::GetMask() const {
    return mask_;
}

