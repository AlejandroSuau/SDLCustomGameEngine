#pragma once

#include "engine/Engine.h"

#include "Particle.h"
#include "engine/Color.h"

#include <vector>
#include <memory>

class Firework {
public:
    Firework(Engine& engine);

    void Update(float dt);
    void Render();

    bool CanBeDestroyed() const;

private:
    Engine& engine_;
    const Color color_;
    Particle* main_particle_;
    std::vector<std::unique_ptr<Particle>> particles_;
    bool can_be_destroyed_;

    void ClearDestroyableParticles();
    void AddExplosionParticles(Vec2 position);
};
