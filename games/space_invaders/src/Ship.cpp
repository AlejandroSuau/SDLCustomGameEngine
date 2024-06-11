#include "space_invaders/include/Ship.h"

#include "space_invaders/include/Constants.h"

Ship::Ship(Engine& engine) 
    : engine_(engine)
    , rect_(engine_.GetWindowWidth() * 0.5f,
            engine_.GetWindowHeight() * 0.9f,
            kShipWidth,
            kShipHeight)
    , movement_state_(EMovementState::NONE) {}
    
void Ship::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    const bool is_key_up = (event_type == EKeyEventType::KEY_UP);
    const bool is_key_down = (event_type == EKeyEventType::KEY_DOWN);
    if (is_key_down) {
        switch(scancode) {
        case SDL_SCANCODE_A:
            movement_state_ = EMovementState::LEFT;
            break;
        case SDL_SCANCODE_D:
            movement_state_ = EMovementState::RIGHT;
            break;
        case SDL_SCANCODE_SPACE:
            SpawnProjectile();
            break;
        }
    } else if (is_key_up) {
        if ((scancode == SDL_SCANCODE_A && IsMovingLeft()) ||
            (scancode == SDL_SCANCODE_D && IsMovingRight())) {
            movement_state_ = EMovementState::NONE;
        }
    }    
}

const Projectile* Ship::GetProjectile() const {
    return projectile_.get();
}

bool Ship::IsMovingRight() const {
    return (movement_state_ == EMovementState::RIGHT);
}

bool Ship::IsMovingLeft() const {
    return (movement_state_ == EMovementState::LEFT);
}

bool Ship::CanSpawnProjectile() const {
    return (projectile_ == nullptr);
}

void Ship::Update(float dt) {
    const float dx = kShipVelocity * dt;
    if (movement_state_ == EMovementState::LEFT) {
        rect_.x -= dx;
    } else if (movement_state_ == EMovementState::RIGHT) {
        rect_.x += dx;
    }

    if (projectile_) {
        projectile_->Update(dt);
        if (!projectile_->IsInsideBounds()) DestroyProjectile();
    }
}

void Ship::Render() {
    engine_.DrawRectangle(rect_);
    if (projectile_) projectile_->Render();
}

void Ship::DestroyProjectile() {
    projectile_ = nullptr;
}

void Ship::SpawnProjectile() {
    if (projectile_) return;
    
    const float x = rect_.x + 0.5f * kShipWidth - 0.5f * kProjectileWidth;
    const float y = rect_.y - kProjectileHeight;
    projectile_ = std::make_unique<Projectile>(engine_, x, y);
}
