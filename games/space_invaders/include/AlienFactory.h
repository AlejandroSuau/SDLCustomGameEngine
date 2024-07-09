#pragma once

#include "engine/Engine.h"

#include "space_invaders/include/Alien.h"

#include <memory>

class AlienFactory {
public:
    AlienFactory(Engine& engine);
    
    std::unique_ptr<Alien> CreateAlien(Vec2 position, std::size_t alien_index);

private:
    Engine& engine_;
    static const std::size_t kAlienTypesCount = 5;
};
