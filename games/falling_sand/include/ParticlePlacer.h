#pragma once

#include "engine/IMouseEventsListener.h"

#include "Grid.h"
#include "ActiveParticleManager.h"

class ParticlePlacer : public IMouseEventsListener {
public:
    ParticlePlacer(Grid& grid, const ActiveParticleManager& active_particle_manager);

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;

private:
    Grid& grid_;
    const ActiveParticleManager& active_particle_manager_;
};
