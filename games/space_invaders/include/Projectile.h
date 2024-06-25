#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

enum class EProjectileDirection {
    UP, DOWN
};

class Projectile {
public:
    Projectile(Engine& engine,  EProjectileDirection direction, float x, float y);

    void Update(float dt);
    void Render();
    bool IsInsideBounds() const;
    bool CollidesWith(const Rectangle& other) const;
    const Rectangle& GetRectangle() const;

private:
    Engine& engine_;
    Rectangle rect_;
    EProjectileDirection current_direction_;
};
