#pragma once

#include "engine/utils/Vec2.h"
#include "engine/Rectangle.h"
#include "engine/Engine.h"

#include <array>
#include <vector>

class DefenseBlock {
public:
    DefenseBlock(Engine& engine, Vec2 position);

    void Render();
    bool ProcessCollisionWith(const Rectangle& rect);

private:
    Engine& engine_;
    int lifes_;
    std::vector<Rectangle> blocks_;

    std::array<std::array<bool, 5>, 5> blocks_design_ {{
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1}
    }};

    void InitBlocks(Vec2 starting_position);
};
