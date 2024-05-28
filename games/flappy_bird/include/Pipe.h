#pragma once

#include "engine/Engine.h"
#include "engine/utils/Vec2.h"

class Pipe {
public:
    static const float kWidth;

    Pipe(Engine& engine, Vec2 position, float height);
    Pipe(Engine& engine, Vec2 position, Vec2 dimension);
    ~Pipe();

    void Update(float dt);
    void Render();
    bool CanBeDestroyed();

private:
    Engine& engine_;
    Vec2 position_;
    Vec2 dimension_;
    std::size_t id_pipe_;
};
