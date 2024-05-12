#include "falling_sand/include/ParticlePlacer.h"

ParticlePlacer::ParticlePlacer(Grid& grid, const ActiveParticleManager& active_particle_manager)
    : grid_(grid)
    , active_particle_manager_(active_particle_manager) {}

void ParticlePlacer::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    if (event_type != EMouseEventType::LEFT_DOWN) return;

    grid_.PlaceParticleInCoords(active_particle_manager_.GetActiveParticleType(), x, y);
}
