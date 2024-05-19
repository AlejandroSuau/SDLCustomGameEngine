#pragma once

#include <vector>

#include "engine/Engine.h"

#include "Particle.h"

class Grid {
public:
    Grid(Engine& engine, int width, int height);

    void UpdateCells(float dt);
    void RenderCells();

    bool AreCoordsInsideBounds(int x, int y) const;
    bool IsWithinBounds(std::size_t row, std::size_t column) const;

    bool PlaceParticleInCoords(Particle& particle, int x, int y);
    Particle& GetParticle(std::size_t row, std::size_t column);
    Particle& PlaceParticle(Particle& new_particle, std::size_t row, std::size_t column);
    void ResetParticle(std::size_t row, std::size_t column);
    void ClearAllParticles();

private:
    Engine& engine_;
    const int width_;
    const int height_;
    std::size_t columns_count_;
    std::size_t rows_count_;

    std::vector<std::vector<Particle>> cells_;

    void InitCells();
};
