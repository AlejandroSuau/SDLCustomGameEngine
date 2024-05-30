#pragma once

#include "engine/Engine.h"
#include "engine/IKeyboardEventsListener.h"
#include "engine/utils/Vec2.h"

#include "Pipe.h"

enum class EBirdState {
    NONE,
    FLYING,
    FALLING
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

    bool CollidesWith(Pipe& pipe) const;
    Rectangle GetRectangle() const;

private:
    Engine& engine_;
    EBirdState current_state_;
    Vec2 position_;
    Vec2 dimension_;
    float velocity_;
};
