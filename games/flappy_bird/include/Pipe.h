#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"

class Pipe {
public:
    static const float kWidth;

    Pipe(Engine& engine, Vec2 position, float height);
    Pipe(Engine& engine, Vec2 position, Vec2 dimension);

    void Update(float dt);
    void Render();
    bool CanBeDestroyed() const;
    Rectangle GetRectangle() const;

private:
    Engine& engine_;
    Vec2 position_;
    Vec2 dimension_;
};
