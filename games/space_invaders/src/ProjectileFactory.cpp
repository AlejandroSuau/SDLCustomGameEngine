#include "space_invaders/include/ProjectileFactory.h"

#include "space_invaders/include/Constants.h"

ProjectileFactory::ProjectileFactory(Engine& engine) 
    : engine_(engine) {}

std::unique_ptr<Projectile> ProjectileFactory::CreateEnemyProjectile(float x, float y) {
    return std::make_unique<Projectile>(engine_, EProjectileDirection::DOWN, x, y, kAlienProjectileLayer, kAlienProjectileMask);
}

std::unique_ptr<Projectile> ProjectileFactory::CreateShipProjectile(float x, float y) {
    return std::make_unique<Projectile>(engine_, EProjectileDirection::UP, x, y, kShipProjectileLayer, kShipProjectileMask);
}
