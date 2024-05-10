#include "falling_sand/include/Particle.h"

#include <unordered_map>

namespace {
    const std::unordered_map<EParticleType, Color> kParticleTypeColorMap {
        {EParticleType::NONE, Color{0, 0, 0, 0}},
        {EParticleType::WALL, Color{18, 25, 25, 255}},
        {EParticleType::SAND, Color{223, 173, 69, 255}},
        {EParticleType::WATER, Color{69, 199, 223, 255}}
    };
}

Particle::Particle(Engine& engine)
    : engine_(engine)
    , type_(EParticleType::WALL)
    , updated_(false) {}

void Particle::Render(float x, float y) {
    const auto& color = kParticleTypeColorMap.find(type_)->second;
    engine_.DrawRectangle({x, y, kParticleSize, kParticleSize}, color);
}
