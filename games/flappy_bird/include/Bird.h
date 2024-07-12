#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"
#include "engine/timer/CountdownTimer.h"

#include <array>

enum class EBirdState {
    STANDING,
    FLYING,
    DYING,
    DEAD
};

class Bird {
public:
    Bird(Engine& engine, float x, float y);

    void Jump();

    void Update(float dt);
    void Render();

    void OnCollisionWithFloor(float floor_y_position);
    void OnCollisionWithPipe();

    void Reset();
    
    const Rectangle& GetHitBox() const;

private:
    Engine& engine_;
    EBirdState current_state_;
    Vec2 starting_position_;
    Rectangle hit_box_;
    float velocity_;
    float oscillation_time_;

    CountdownTimer flying_animation_timer_;
    std::array<SDL_Texture*, 3> flying_textures_;
    std::size_t current_fly_texture_index_;

    void LoadTextures();
    void UpdateFallingPosition(float dt);
    void UpdateAnimationFlying(float dt);
    void UpdateAnimationStanding(float dt);
};
