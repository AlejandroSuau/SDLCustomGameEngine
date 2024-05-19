#pragma once

#include "Grid.h"
#include "Particle.h"

class ParticleMover {
public:
    static bool MoveParticle(Grid& grid, Particle& particle, std::size_t row, std::size_t column);
    
private:
    static bool MoveSand(Grid& grid, Particle& particle, std::size_t row, std::size_t column);
    static bool MoveWater(Grid& grid, Particle& particle, std::size_t row, std::size_t column);
};
