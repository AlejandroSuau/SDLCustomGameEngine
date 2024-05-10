#pragma once

#include "engine/Engine.h"

enum class EParticleType {
    NONE, SAND, WALL, WATER
};

class Particle {
public:
    static const int kParticleSize = 20;

    Particle(Engine& engine);

    void Render(float x, float y);

private:
    Engine& engine_;
    EParticleType type_;
    bool updated_;
};
