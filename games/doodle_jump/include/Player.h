#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/collision/ICollidable.h"
#include "engine/IKeyboardEventsListener.h"

#include "engine/utils/Vec2.h"

enum class EPlayerState {
    FALLING, JUMPING
};

enum class EPlayerDirection {
    NONE, LEFT, RIGHT
};

class Player : public IKeyboardEventsListener, public ICollidable {
public:
    Player(Engine& engine);
    ~Player();

    void Update(float dt);
    void Render();

    void Jump(float jump_force);

    bool IsJumping() const;
    bool IsFalling() const;
    Vec2 GetPosition() const;

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

    // ICollidable
    const Rectangle& GetBoundingBox() const override;
    void OnCollision(ICollidable& other) override;

    unsigned int GetLayer() const override;
    unsigned int GetMask() const override;

private:
    Engine& engine_;
    Vec2 velocity_;
    Rectangle rect_;
    EPlayerState state_;
    EPlayerDirection direction_;
};
