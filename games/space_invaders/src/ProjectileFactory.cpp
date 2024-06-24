#include "space_invaders/include/ProjectileFactory.h"

ProjectileFactory::ProjectileFactory(Engine& engine) 
    : engine_(engine) {}

std::unique_ptr<Projectile> ProjectileFactory::CreateEnemyProjectile(float x, float y) {
    return std::make_unique<Projectile>(engine_, EProjectileDirection::DOWN, x, y);
}

std::unique_ptr<Projectile> ProjectileFactory::CreateShipProjectile(float x, float y) {
    return std::make_unique<Projectile>(engine_, EProjectileDirection::UP, x, y);
}
