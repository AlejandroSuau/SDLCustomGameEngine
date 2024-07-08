#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/collision/ICollidable.h"

#include "Projectile.h"
#include "ProjectileFactory.h"

#include <memory>

enum class EMovementState {
    NONE, RIGHT, LEFT
};

class Ship : public IKeyboardEventsListener, ICollidable {
public:
    Ship(Engine& engine, ProjectileFactory& projectile_factory);
    ~Ship();

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

    void Update(float dt);
    void Render();
    
    bool CanSpawnProjectile() const;
    void SpawnProjectile();
    void DestroyProjectile();
    bool IsAlive() const;
    void Hit();

    // ICollidable
    const Rectangle& GetBoundingBox() const override;
    void OnCollision(ICollidable& other) override;
    unsigned int GetLayer() const override;
    unsigned int GetMask() const override;

private:
    Engine& engine_;
    ProjectileFactory& projectile_factory_;
    int lifes_;
    Rectangle rect_;
    EMovementState movement_state_;
    std::unique_ptr<Projectile> projectile_;

    bool IsMovingRight() const;
    bool IsMovingLeft() const;
};
