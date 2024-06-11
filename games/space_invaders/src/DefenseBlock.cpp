#include "space_invaders/include/DefenseBlock.h"

#include "space_invaders/include/Constants.h"

DefenseBlock::DefenseBlock(Engine& engine, Vec2 position) 
    : engine_(engine)
    , rect_(position.x, position.y, kDefenseBlockWidth, kDefenseBlockHeight)
    , lifes_(kDefenseBlockLifes) {}

void DefenseBlock::Hit() {
    --lifes_;
}

void DefenseBlock::Render() {
    engine_.DrawRectangle(rect_);
}

const Rectangle& DefenseBlock::GetRectangle() const {
    return rect_;
}

bool DefenseBlock::IsAlive() const {
    return (lifes_ > 0);
}
