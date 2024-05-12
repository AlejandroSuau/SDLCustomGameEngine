#pragma once

#include <vector>

#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Particle.h"

class Grid {
public:
    Grid(Engine& engine, int width, int height);

    void UpdateCells(float dt);
    void RenderCells();

    bool PlaceParticleInCoords(EParticleType particle_type, int x, int y);
    bool AreCoordsInsideBounds(int x, int y) const;
    bool IsFreeForPlacing(std::size_t row, std::size_t column) const;
    void PlaceParticle(EParticleType particle_type, std::size_t row, std::size_t column);
    void ClearAllParticles();

private:
    Engine& engine_;
    const int width_;
    const int height_;
    CountdownTimer tick_timer_;
    std::size_t columns_count_;
    std::size_t rows_count_;

    std::vector<std::vector<Particle>> cells_;

    void InitCells();
};
