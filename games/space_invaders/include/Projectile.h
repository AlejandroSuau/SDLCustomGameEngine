#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

class Projectile {
public:
    Projectile(Engine& engine, float x, float y);

    void Update(float dt);
    void Render();
    bool IsInsideBounds() const;
    bool CollidesWith(const Rectangle& other) const;

private:
    Engine& engine_;
    Rectangle rect_;
};
