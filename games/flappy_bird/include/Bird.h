#pragma once

#include "engine/Engine.h"
#include "engine/IKeyboardEventsListener.h"

#include "Bird.h"

enum class EBirdState {
    NONE,
    FLYING,
    FALLING
};

struct Vec2 {
    float x, y;
    Vec2(float x_ = 0.f, float y_ = 0.f) : x(x_), y(y_) {}
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

    bool IsFlying() const;
    bool IsFalling() const;

private:
    Engine& engine_;
    EBirdState current_state_;
    Vec2 position_;
    Vec2 dimension_;
};
