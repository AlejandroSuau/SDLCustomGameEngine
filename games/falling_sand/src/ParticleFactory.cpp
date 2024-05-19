#include "falling_sand/include/ParticleFactory.h"

#include <cassert>
#include <unordered_map>
#include <array>

namespace {

const std::size_t kColorsPerParticle = 3;
const std::unordered_map<EParticleType, std::array<Color, kColorsPerParticle>> kParticleTypeColorMap {
    {EParticleType::NONE, {{{0, 0, 0, 255}, {0, 0, 0, 255}, {0, 0, 0, 255}}}},
    {EParticleType::SAND, {{{166, 145, 80, 255}, {177, 157, 94, 255}, {186, 168, 111, 255}}}},
    {EParticleType::WALL, {{{188, 188, 186, 255}, {201, 201, 199, 255}, {213, 213, 212, 255}}}},
    {EParticleType::WATER, {{{2, 184, 215, 255}, {3, 205, 240, 255}, {16, 217, 252, 255}}}},
};

}

ParticleFactory::ParticleFactory(Engine& engine)
    : engine_(engine)
    , current_particle_color_index_(0) {
    
    color_indexes_.reserve(kColorsSize);
    int color_particle_index = 0;
    for (std::size_t i = 0; i < static_cast<int>(kColorsSize); ++i) {
        color_indexes_.push_back(color_particle_index);
        color_particle_index++;
        if (color_particle_index >= kColorsPerParticle) {
            color_particle_index = 0;
        }
    }
    
    auto& random_generator = engine_.GetRandomGenerator();
    random_generator.ShuffleNumbers(color_indexes_);
}

std::unique_ptr<Particle> ParticleFactory::CreateParticle(EParticleType particle_type) {
    switch(particle_type) {
        case EParticleType::WALL:  return CreateParticleWall();
        case EParticleType::SAND:  return CreateParticleSand();
        case EParticleType::WATER: return CreateParticleWater();
        default:
            assert(false);
            return nullptr;
    }
}

std::unique_ptr<Particle> ParticleFactory::CreateParticleWall() {
    const auto& colors = kParticleTypeColorMap.find(EParticleType::WALL)->second;
    const auto color_index = color_indexes_[current_particle_color_index_];
    auto particle = std::make_unique<Particle>(engine_, EParticleType::WALL, colors[color_index]);
    IncreaseParticleColorIndex();
    return particle;
}

std::unique_ptr<Particle> ParticleFactory::CreateParticleWater() {
    const auto& colors = kParticleTypeColorMap.find(EParticleType::WATER)->second;
    const auto color_index = color_indexes_[current_particle_color_index_];
    auto particle = std::make_unique<Particle>(engine_, EParticleType::WATER, colors[color_index]);
    IncreaseParticleColorIndex();
    return particle;
}

std::unique_ptr<Particle> ParticleFactory::CreateParticleSand() {
    const auto& colors = kParticleTypeColorMap.find(EParticleType::SAND)->second;
    const auto color_index = color_indexes_[current_particle_color_index_];
    auto particle = std::make_unique<Particle>(engine_, EParticleType::SAND, colors[color_index]);
    IncreaseParticleColorIndex();
    return particle;
}

void ParticleFactory::IncreaseParticleColorIndex() {
    ++current_particle_color_index_;
    if (current_particle_color_index_ >= kColorsSize) {
        current_particle_color_index_ = 0;
    }
}

