#pragma once

#include "engine/Engine.h"
#include "engine/utils/Vec2.h"
#include "engine/timer/CountdownTimer.h"

#include "Alien.h"
#include "AlienFactory.h"
#include "Projectile.h"

#include <vector>
#include <memory>

class AlienList {
public:
    AlienList(Engine& engine, std::size_t aliens_count);

    void Update(float dt);
    void Render();
    bool DidProjectileDestroyAnAlien(const Projectile& projectile);

private:
    Engine& engine_;
    AlienFactory alien_factory_;
    std::vector<std::unique_ptr<Alien>> aliens_;
    const std::size_t aliens_count_;
    const Vec2 starting_position_;
    const Vec2 ending_position_;
    CountdownTimer step_timer_;
    EAlienMovementDirection movement_direction_;
    float movement_direction_scalar_;

    float pack_x_bound_left_;
    float pack_x_bound_right_;

    float max_spawn_interval_;
    float min_spawn_interval_;
    CountdownTimer spawn_projectile_timer_;
    std::vector<std::unique_ptr<Projectile>> projectiles_;

    void InitializeAliens();
    bool IsMovingDown() const;
    void SwapMovementDirection();
    void MovePackBounds();

    Alien* GetRandomAlien();
    void SpawnProjectile();
    void CleanProjectilesOutOfBounds();
};