#pragma once

#include "engine/Engine.h"

#include "Particle.h"
#include "engine/Color.h"

#include <vector>
#include <memory>

class Firework {
public:
    Firework(Engine& engine);

    void Update(float dt);
    void Render();

private:
    Engine& engine_;
    Vec2 pos_;
    Vec2 vel_;
    Vec2 acc_;
    float direction_;
    float angle_;
};
