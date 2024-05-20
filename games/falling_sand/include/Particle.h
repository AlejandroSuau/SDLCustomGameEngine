#pragma once

#include "engine/Engine.h"

class Grid;

enum class EParticleType {
    NONE,
    SAND,
    WALL,
    WATER,
    SMOKE,
    //FIRE,
    //WOOD
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
    std::size_t GetGridTicksCount() const;
    bool IsUpdated() const;
    void SetUpdated(bool updated);
    void SetToNone();
    void ReplaceParticle(Particle& new_particle);
    void IncreaseGridTicksCount();

private:
    Engine& engine_;
    EParticleType type_;
    Color color_;
    std::size_t grid_ticks_count_;
    bool updated_;
};
