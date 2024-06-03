#pragma once

#include "engine/Engine.h"
#include "engine/IKeyboardEventsListener.h"
#include "engine/utils/Vec2.h"

#include "Pipe.h"

enum class EBirdState {
    STANDING,
    FLYING,
    FALLING,
    DYING,
    DEAD
};

class Bird : public IKeyboardEventsListener {
public:
    Bird(Engine& engine);

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

    void Update(float dt);
    void Render();
    
    void SetStateFalling();
    void SetStateFlying();
    void SetStateDying();
    void SetStateDead();

    bool IsStanding() const;
    bool IsFlying() const;
    bool IsFalling() const;
    bool IsDead() const;
    bool IsDying() const;

    const Vec2& GetDimension() const;
    void SetPositionY(float y);

    bool CollidesWith(Pipe& pipe) const;
    Rectangle GetRectangle() const;

private:
    Engine& engine_;
    EBirdState current_state_;
    Vec2 position_;
    Vec2 dimension_;
    float velocity_;
    float oscillation_time_;
};
