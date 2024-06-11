#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"

enum class EAlienMovementDirection {
    RIGHT,
    LEFT,
    DOWN
};

class Alien {
public:
    Alien(Engine& engine, Vec2 position);

    void MovementStep(EAlienMovementDirection movement_direction);
    void Render();

    void SetStateMovingRight();
    void SetStateMovingLeft();

    void Hit();

    void SetPosition(Vec2 position);
    Vec2 GetPosition() const;
    bool IsAlive() const;

    const Rectangle& GetRectangle() const;

private:
    Engine& engine_;
    Rectangle rect_;
    int lifes_;
};
