#include "falling_sand/include/Particle.h"

#include "falling_sand/include/Grid.h"

#include <unordered_map>

namespace {
    const std::unordered_map<EParticleType, Color> kParticleTypeColorMap {
        {EParticleType::NONE, Color{255, 255, 255, 255}},
        {EParticleType::WALL, Color{18, 25, 25, 255}},
        {EParticleType::SAND, Color{223, 173, 69, 255}},
        {EParticleType::WATER, Color{69, 199, 223, 255}}
    };
}

Particle::Particle(Engine& engine)
    : engine_(engine)
    , type_(EParticleType::NONE)
    , updated_(false) {}

void Particle::GridTick(Grid& grid, EParticleType particle_type, std::size_t row, std::size_t column) {
    if (particle_type == EParticleType::SAND) {
        bool did_place_particle;
        if (grid.IsFreeForPlacing(row + 1, column)) {
            grid.PlaceParticle(particle_type, row + 1, column);
            did_place_particle = true;
        } else if (grid.IsFreeForPlacing(row + 1, column - 1)) {
            grid.PlaceParticle(particle_type, row + 1, column - 1);
            did_place_particle = true;
        } else if (grid.IsFreeForPlacing(row + 1, column + 1)) {
            grid.PlaceParticle(particle_type, row + 1, column + 1);
            did_place_particle = true;
        } else {
            did_place_particle = false;
        }

        if (did_place_particle) grid.PlaceParticle(EParticleType::NONE, row, column);
    }
}

void Particle::SetUpdated(bool updated) {
    updated_ = updated;
}

EParticleType Particle::GetParticleType() const {
    return type_;
}

void Particle::Render(float x, float y) {
    const auto& color = kParticleTypeColorMap.find(type_)->second;
    engine_.DrawRectangle({x, y, kParticleSize, kParticleSize}, color, true);
}

void Particle::SetParticleType(EParticleType particle_type) {
    type_ = particle_type;
}

bool Particle::IsUpdated() const {
    return updated_;
}
