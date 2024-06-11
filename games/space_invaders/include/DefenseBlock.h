#pragma once

#include "engine/utils/Vec2.h"
#include "engine/Rectangle.h"
#include "engine/Engine.h"

class DefenseBlock {
public:
    DefenseBlock(Engine& engine, Vec2 position);

    void Hit();
    void Render();
    bool IsAlive() const;
    const Rectangle& GetRectangle() const;

private:
    Engine& engine_;
    Rectangle rect_;
    int lifes_;
};
