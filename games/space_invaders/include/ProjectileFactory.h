#pragma once

#include "engine/Engine.h"

#include "Projectile.h"

#include <memory>

class ProjectileFactory {
public:
    ProjectileFactory(Engine& engine);

    std::unique_ptr<Projectile> CreateEnemyProjectile(float x, float y);
    std::unique_ptr<Projectile> CreateShipProjectile(float x, float y);

private:
    Engine& engine_;
};
