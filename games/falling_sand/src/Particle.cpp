#include "falling_sand/include/Particle.h"

#include "falling_sand/include/Grid.h"
#include "falling_sand/include/ParticleMover.h"

#include <array>
#include <unordered_map>

Particle::Particle(Engine& engine, EParticleType particle_type, Color color)
    : engine_(engine)
    , type_(particle_type)
    , color_(color)
    , updated_(false) {}

Particle::Particle(Engine& engine)
    : engine_(engine)
    , type_(EParticleType::NONE)
    , color_(0, 0, 0, 255)
    , updated_(false) {}

void Particle::GridTick(Grid& grid, std::size_t row, std::size_t column) {
    const auto did_move_particle = ParticleMover::MoveParticle(grid, *this, row, column);
}

void Particle::SetUpdated(bool updated) {
    updated_ = updated;
}

EParticleType Particle::GetType() const {
    return type_;
}

const Color& Particle::GetColor() const {
    return color_;
}

void Particle::Render(float x, float y) {
    engine_.DrawRectangle({x, y, kParticleSize, kParticleSize}, color_, true);
}

void Particle::SetToNone() {
    type_ = EParticleType::NONE;
    color_ = {0, 0, 0, 255}; // TODO: Get it from the map.
}

void Particle::SetParticleTypeAndColor(EParticleType particle_type, Color color) {
    type_ = particle_type;
    color_ = color;
}

bool Particle::IsUpdated() const {
    return updated_;
}
