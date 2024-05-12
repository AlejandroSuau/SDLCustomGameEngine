#pragma once

#include "engine/Engine.h"

class Grid;

enum class EParticleType {
    NONE, SAND, WALL, WATER
};

class Particle {
public:
    static const int kParticleSize = 20;

    Particle(Engine& engine);

    void GridTick(Grid& grid, EParticleType particle_type, std::size_t row, std::size_t column);
    void Render(float x, float y);
    void SetParticleType(EParticleType particle_type);
    EParticleType GetParticleType() const;
    bool IsUpdated() const;
    void SetUpdated(bool updated);

private:
    Engine& engine_;
    EParticleType type_;
    bool updated_;
};
