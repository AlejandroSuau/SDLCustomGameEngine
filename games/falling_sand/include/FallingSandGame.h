#pragma once

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Grid.h"
#include "ActiveParticleManager.h"
#include "ParticlePlacer.h"

class FallingSandGame : public IGame {
public:
    FallingSandGame();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Grid grid_;
    ActiveParticleManager active_particle_manager_;
    ParticlePlacer particle_placer_;
    CountdownTimer grid_tick_timer_;
};
