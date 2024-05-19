#pragma once

#include "engine/Engine.h"

#include "falling_sand/include/Particle.h"

#include <memory>
#include <vector>

class ParticleFactory {
public:
    ParticleFactory(Engine& engine);
    std::unique_ptr<Particle> CreateParticle(EParticleType particle_type);

private:
    Engine& engine_;

    std::size_t current_particle_color_index_;
    std::vector<int> color_indexes_;
    const std::size_t kColorsSize = 11;

    std::unique_ptr<Particle> CreateParticleWall();
    std::unique_ptr<Particle> CreateParticleWater();
    std::unique_ptr<Particle> CreateParticleSand();
    std::unique_ptr<Particle> CreateParticleSmoke();

    void IncreaseParticleColorIndex();
};
