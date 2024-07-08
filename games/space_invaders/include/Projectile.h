#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/collision/ICollidable.h"

enum class EProjectileDirection {
    UP, DOWN
};

class Projectile : public ICollidable {
public:
    Projectile(
        Engine& engine, 
        EProjectileDirection direction,
        float x,
        float y,
        unsigned int layer,
        unsigned int mask);
    ~Projectile();

    void Update(float dt);
    void Render();
    bool IsInsideBounds() const;
    void MarkForDestroy();
    bool IsMarkedForDestroy() const;

    // ICollidable
    const Rectangle& GetBoundingBox() const override;
    void OnCollision(ICollidable& other) override;
    unsigned int GetLayer() const override;
    unsigned int GetMask() const override;

private:
    Engine& engine_;
    Rectangle rect_;
    EProjectileDirection current_direction_;
    unsigned int layer_;
    unsigned int mask_;
    bool is_marked_for_destroy_;
};
