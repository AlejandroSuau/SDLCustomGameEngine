#pragma once

#include "engine/IMouseEventsListener.h"

#include "Grid.h"
#include "ActiveParticleManager.h"
#include "ParticleFactory.h"

class ParticlePlacer : public IMouseEventsListener {
public:
    ParticlePlacer(Engine& engine, Grid& grid, const ActiveParticleManager& active_particle_manager);

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;

private:
    ParticleFactory particle_factory_;
    Grid& grid_;
    const ActiveParticleManager& active_particle_manager_;
};
