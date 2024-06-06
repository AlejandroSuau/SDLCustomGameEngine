#pragma once

#include "engine/Engine.h"
#include "engine/IKeyboardEventsListener.h"
#include "engine/utils/Vec2.h"
#include "engine/timer/CountdownTimer.h"

#include "Pipe.h"

#include <array>

enum class EBirdState {
    STANDING,
    FLYING,
    DYING,
    DEAD
};

class Bird : public IKeyboardEventsListener {
public:
    Bird(Engine& engine, float x, float y);

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

    void Update(float dt);
    void Render();

    void OnCollisionWithFloor(float floor_y_position);
    void OnCollisionWithPipe();
    
    void SetStateFlying();
    void SetStateDying();
    void SetStateDead();

    bool IsStanding() const;
    bool IsFlying() const;
    bool IsDead() const;
    bool IsDying() const;

    const Vec2& GetDimension() const;
    bool CollidesWith(Pipe& pipe) const;
    Rectangle GetRectangle() const;

    void Reset();

private:
    Engine& engine_;
    EBirdState current_state_;
    const Vec2 starting_position_;
    Vec2 position_;
    Vec2 dimension_;
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
