#pragma once

#include <vector>

#include "engine/Engine.h"

#include "Particle.h"

class Grid {
public:
    Grid(Engine& engine, int width, int height);

    void UpdateCells(float dt);
    void RenderCells();
    
private:
    Engine& engine_;
    const int width_;
    const int height_;

    std::vector<std::vector<Particle>> cells_;

    void InitCells();
};
