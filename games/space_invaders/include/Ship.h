#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

#include "Projectile.h"

#include <memory>

enum class EMovementState {
    NONE, RIGHT, LEFT
};

class Ship : public IKeyboardEventsListener {
public:
    Ship(Engine& engine);
    
    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

    void Update(float dt);
    void Render();
    
    bool CanSpawnProjectile() const;
    void SpawnProjectile();
    void DestroyProjectile();
    const Projectile* GetProjectile() const;

private:
    Engine& engine_;
    Rectangle rect_;
    EMovementState movement_state_;
    std::unique_ptr<Projectile> projectile_;

    bool IsMovingRight() const;
    bool IsMovingLeft() const;
};
