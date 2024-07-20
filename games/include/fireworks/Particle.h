#pragma once

#include "engine/Engine.h"
#include "engine/utils/Vec2.h"
#include "engine/animation/FadeOutColorAnimation.h"

#include <memory>

class Particle {
public:
    Particle(
        Engine& engine,
        Color color,
        Vec2 position, 
        Vec2 velocity,
        float radius,
        bool has_fade_animation = false,
        bool is_trail_active = false,
        bool is_applying_gravity_ = true);

    void Update(float dt);
    void Render();

    void ApplyForce(Vec2 force);

    const Vec2& GetPosition() const;
    const Vec2& GetVelocity() const;
    void SetVelocity(Vec2 velocity); 

    bool CanBeDestroyed() const;

private:
    Engine& engine_;
    Color color_;
    Vec2 position_;
    Vec2 velocity_;
    Vec2 acceleration_;
    float radius_;
    bool can_be_destroyed;
    std::unique_ptr<FadeOutColorAnimation> fade_animation_;
    bool is_trail_active_;
    bool is_applying_gravity_;

    std::vector<Vec2> trail_positions_;
    void RenderTrail();
};
