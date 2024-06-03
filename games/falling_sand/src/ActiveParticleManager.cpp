#include "falling_sand/include/ActiveParticleManager.h"

#include <unordered_map>
#include <array>

namespace {
    const std::unordered_map<SDL_Scancode, EParticleType> kKeyParticleTypeMap {
        {SDL_Scancode::SDL_SCANCODE_W, EParticleType::WALL},
        {SDL_Scancode::SDL_SCANCODE_S, EParticleType::SAND},
        {SDL_Scancode::SDL_SCANCODE_A, EParticleType::WATER},
        {SDL_Scancode::SDL_SCANCODE_H, EParticleType::SMOKE},
    };
}

ActiveParticleManager::ActiveParticleManager() 
    : active_particle_type_(EParticleType::NONE) {}

void ActiveParticleManager::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (event_type != EKeyEventType::KEY_UP) return;

    const auto found_particle = kKeyParticleTypeMap.find(scancode);
    if (found_particle != kKeyParticleTypeMap.end()) {
        active_particle_type_ = found_particle->second;
    }
}

bool ActiveParticleManager::HasAnyActiveParticleType() const {
    return (active_particle_type_ != EParticleType::NONE);
}

EParticleType ActiveParticleManager::GetActiveParticleType() const {
    return active_particle_type_;
}
