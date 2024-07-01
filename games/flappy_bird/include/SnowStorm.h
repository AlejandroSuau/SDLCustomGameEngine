#pragma once

#include "engine/Engine.h"
#include "engine/RandomGenerator.h"
#include "engine/timer/CountdownTimer.h"
#include "engine/utils/Vec2.h"

#include <vector>

struct SnowFlake {
    Vec2 position;
    Vec2 velocity;
    SnowFlake(Vec2 p, Vec2 v)
        : position(p), velocity(v) {}
};

class SnowStorm {
public:
    SnowStorm(Engine& engine, float wind);
    
    void Update(float dt);
    void Render();

    void AddSnowFlake();
    void RemoveOutOfBoundsSnowFlakes();
    void CleanStorm();

private:
    Engine& engine_;
    CountdownTimer snow_flakes_spawn_timer_;
    std::vector<SnowFlake> snow_flakes_;

    void InitializeSnowFlakes();
};
