#include "falling_sand/include/ParticlePlacer.h"

ParticlePlacer::ParticlePlacer(Engine& engine, Grid& grid, const ActiveParticleManager& active_particle_manager)
    : particle_factory_(engine)
    , grid_(grid)
    , active_particle_manager_(active_particle_manager) {}

void ParticlePlacer::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    if (event_type != EMouseEventType::LEFT_DOWN) return;

    auto particle = particle_factory_.CreateParticle(active_particle_manager_.GetActiveParticleType());
    grid_.PlaceParticleInCoords(*particle.get(), x, y);
}
