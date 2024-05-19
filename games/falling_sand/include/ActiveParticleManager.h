#pragma once

#include "engine/IKeyboardEventsListener.h"

#include "Particle.h"

class ActiveParticleManager : public IKeyboardEventsListener {
public:
    ActiveParticleManager();
    
    bool HasAnyActiveParticleType() const;
    EParticleType GetActiveParticleType() const;

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    EParticleType active_particle_type_;
};
