#include "space_invaders/include/DefenseBlock.h"

#include "space_invaders/include/Constants.h"

DefenseBlock::DefenseBlock(Engine& engine, Vec2 position) 
    : engine_(engine)
    , lifes_(kDefenseBlockLifes) {
    InitBlocks(position);
}

void DefenseBlock::InitBlocks(Vec2 starting_position) {
    float x = starting_position.x;
    float y = starting_position.y;
    for (auto& blocks_line_ : blocks_design_) {
        x = starting_position.x;
        for (bool should_insert_block : blocks_line_) {
            if (should_insert_block) {
                blocks_.emplace_back(x, y, kDefenseBlockWidth, kDefenseBlockHeight);
            }
            x += kDefenseBlockWidth;
        }
        y += kDefenseBlockHeight;
    }
}

bool DefenseBlock::ProcessCollisionWith(const Rectangle& rect) {
    bool found_collision = false;
    auto it = blocks_.begin();
    while (!found_collision && it != blocks_.end()) {
        if (rect.CollidesWith(*it)) {
            found_collision = true;
            it = blocks_.erase(it);
        } else {
            ++it;
        }
    }
    
    return found_collision;
}

void DefenseBlock::Render() {
    for (auto& block : blocks_) {
        engine_.DrawRectangle(block);
    }
}
