#pragma once

#include "engine/Engine.h"

class Grid;

enum class EParticleType {
    NONE, SAND, WALL, WATER
};

class Particle {
public:
    static const int kParticleSize = 10;

    Particle(Engine& engine);
    Particle(Engine& engine, EParticleType particle_type, Color color);

    void GridTick(Grid& grid, std::size_t row, std::size_t column);
    void Render(float x, float y);
    void SetParticleTypeAndColor(EParticleType particle_type, Color color);
    EParticleType GetType() const;
    const Color& GetColor() const;
    bool IsUpdated() const;
    void SetUpdated(bool updated);
    void SetToNone();
    
private:
    Engine& engine_;
    EParticleType type_;
    Color color_;
    bool updated_;
};
