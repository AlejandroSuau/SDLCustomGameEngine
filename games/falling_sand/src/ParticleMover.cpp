#include "falling_sand/include/ParticleMover.h"

#include <cassert>
#include <utility>
#include <array>
#include <iostream>
#include <random>

bool ParticleMover::MoveParticle(Grid& grid, Particle& particle, std::size_t row, std::size_t column) {
    switch(particle.GetType()) {
        case EParticleType::SAND:
            return MoveSand(grid, particle, row, column);
        case EParticleType::WATER:
            return MoveWater(grid, particle, row, column);
        case EParticleType::SMOKE:
            return MoveSmoke(grid, particle, row, column);
        default:
            return false;
    }
}

bool ParticleMover::MoveSand(Grid& grid, Particle& particle, std::size_t row, std::size_t column) {
    std::array<std::pair<std::size_t, std::size_t>, 3> movements {{
        {row + 1, column},
        {row + 1, column - 1},
        {row + 1, column + 1}
    }};

    std::size_t move_idx = 0;
    bool did_move = false;
    while (move_idx < movements.size() && !did_move) {
        const auto& row_col = movements[move_idx];
        ++move_idx;
        if (!grid.IsWithinBounds(row_col.first, row_col.second)) {
            continue;
        }

        auto& new_particle = grid.GetParticle(row_col.first, row_col.second);
        auto new_particle_type = new_particle.GetType();
        bool is_movable = (new_particle_type == EParticleType::NONE ||
                           new_particle_type == EParticleType::WATER);
        if (is_movable) {
            grid.PlaceParticle(particle, row_col.first, row_col.second);
            particle.SetUpdated(true);
            did_move = true;
        }
    }

    if (did_move) {
        grid.ResetParticle(row, column);
    }
    
    return did_move;
}

bool ParticleMover::MoveWater(Grid& grid, Particle& particle, std::size_t row, std::size_t column) {
    std::array<std::pair<std::size_t, std::size_t>, 5> movements {{
        {row + 1, column},
        {row + 1, column - 1},
        {row + 1, column + 1},
        {row, column + 1},
        {row, column - 1},
    }};

    // Aleatoriedad 50% para moverse a la derecha o a la izquierda.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    if (dis(gen) == 0) {
        std::swap(movements[3], movements[4]);
    }

    std::size_t move_idx = 0;
    bool did_move = false;
    while (move_idx < movements.size() && !did_move) {
        const auto& row_col = movements[move_idx];
        ++move_idx;
        if (!grid.IsWithinBounds(row_col.first, row_col.second)) {
            continue;
        }
        
        auto& new_particle = grid.GetParticle(row_col.first, row_col.second);
        did_move = (new_particle.GetType() == EParticleType::NONE);
        if (did_move) {
            grid.PlaceParticle(particle, row_col.first, row_col.second);
            new_particle.SetUpdated(true);
        }
    }

    if (did_move) {
        grid.ResetParticle(row, column);
    }

    return did_move;
}

bool ParticleMover::MoveSmoke(Grid& grid, Particle& particle, std::size_t row, std::size_t column) {
    std::array<std::pair<std::size_t, std::size_t>, 3> movements {{
        {row - 1, column},
        {row - 1, column - 1},
        {row - 1, column + 1}
    }};

    std::size_t move_idx = 0;
    bool did_move = false;
    while (move_idx < movements.size() && !did_move) {
        const auto& row_col = movements[move_idx];
        ++move_idx;
        if (!grid.IsWithinBounds(row_col.first, row_col.second)) {
            continue;
        }

        auto& new_particle = grid.GetParticle(row_col.first, row_col.second);
        auto new_particle_type = new_particle.GetType();
        bool is_movable = (new_particle_type == EParticleType::NONE);
        if (is_movable) {
            auto& placed_particle = grid.PlaceParticle(particle, row_col.first, row_col.second);
            placed_particle.SetUpdated(true);
            did_move = true;
        }
    }

    if (did_move) {
        grid.ResetParticle(row, column);
    }
    
    return did_move;
}
