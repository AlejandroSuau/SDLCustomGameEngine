#include "flappy_bird/include/SnowStorm.h"

#include <iostream>

SnowStorm::SnowStorm(Engine& engine, float wind)
    : engine_(engine)
    , snow_flakes_spawn_timer_(0.5f) {
    // InitializeSnowFlakes();
}

void SnowStorm::InitializeSnowFlakes() {
    for (std::size_t i = 0; i < 100; ++i) {
        AddSnowFlake();
    }
}
    
void SnowStorm::Update(float dt) {
    snow_flakes_spawn_timer_.Update(dt);
    if (snow_flakes_spawn_timer_.DidFinish()) {
        snow_flakes_spawn_timer_.Reset();

        auto& random_generator = engine_.GetRandomGenerator();
        auto random_x = random_generator.Generate(0.25f, 2.f);
        snow_flakes_spawn_timer_.SetSecondsToFinish(random_x);
        std::size_t snow_flakes_tick_count = 10;
        for (std::size_t i = 0; i < snow_flakes_tick_count; ++i) {
            AddSnowFlake();
        }
    }

    for (auto& snow_flake : snow_flakes_) {
        snow_flake.position.x -= snow_flake.velocity.x * dt; 
        snow_flake.position.y += snow_flake.velocity.y * dt;
    }

    RemoveOutOfBoundsSnowFlakes();
}

void SnowStorm::Render() {
    for (auto& snow_flake : snow_flakes_) {
        engine_.DrawRectangle(
            Rectangle{snow_flake.position.x, snow_flake.position.y, 3.f, 3.f},
            Color{255, 255, 255, 255},
            true);
    }
}

void SnowStorm::AddSnowFlake() {
    float y_pos = -50.f;
    auto& random_generator = engine_.GetRandomGenerator();
    int min_x_pos = 50;
    int max_x_pos = engine_.GetWindowWidth() + 300;
    auto random_x = static_cast<float>(random_generator.Generate(min_x_pos, max_x_pos));
    
    int min_x_velocity = 20;
    int max_x_velocity = 30;
    auto random_x_velocity = static_cast<float>(random_generator.Generate(min_x_velocity, max_x_velocity));

    int min_y_velocity = 20;
    int max_y_velocity = 30;
    auto random_y_velocity = static_cast<float>(random_generator.Generate(min_y_velocity, max_y_velocity));
    snow_flakes_.emplace_back(
        Vec2{random_x, y_pos}, 
        Vec2{random_x_velocity, random_y_velocity});
}

void SnowStorm::RemoveOutOfBoundsSnowFlakes() {
    int window_height = engine_.GetWindowHeight();
    auto isSnowFlakeOutsideBounds = [window_height](const SnowFlake& snow_flake) {
        return (snow_flake.position.x < 0 || snow_flake.position.y >= window_height); };
    
    snow_flakes_.erase(
        std::remove_if(snow_flakes_.begin(), snow_flakes_.end(), isSnowFlakeOutsideBounds),
        snow_flakes_.end());
}

void SnowStorm::CleanStorm() {
    snow_flakes_.clear();
}
