#include "space_invaders/include/DefenseBlock.h"

#include "space_invaders/include/Constants.h"
#include "space_invaders/include/Projectile.h"

#include <algorithm>

DefenseBlock::Block::Block(Engine& engine, Rectangle rect) 
    : engine_(engine)
    , rect_(rect)
    , is_marked_for_destroy_(false) {
    engine_.GetCollisionManager().AddCollidable(*this);
}

DefenseBlock::Block::~Block() {
    engine_.GetCollisionManager().RemoveCollidable(*this);
}

const Rectangle& DefenseBlock::Block::GetBoundingBox() const {
    return rect_;
}

void DefenseBlock::Block::OnCollision(ICollidable& other) {
    // Avoid colliding with 2 blocks with the same shot
    if (auto* projectile = dynamic_cast<Projectile*>(&other)) {
        if (!projectile->IsMarkedForDestroy()) {
            is_marked_for_destroy_ = true;
        }
    }
}

bool DefenseBlock::Block::IsMarkedForDestroy() const {
    return is_marked_for_destroy_;
}

unsigned int DefenseBlock::Block::GetLayer() const {
    return kDefenseBlockLayer;
}

unsigned int DefenseBlock::Block::GetMask() const {
    return kDefenseBlockMask;
}

void DefenseBlock::Block::Render() {
    engine_.DrawRectangle(rect_, {119, 221, 119, 225}, true);
}

DefenseBlock::DefenseBlock(Engine& engine, Vec2 position) 
    : engine_(engine)
    , lifes_(kDefenseBlockLifes) {
    InitBlocks(position);
}    

void DefenseBlock::InitBlocks(Vec2 starting_position) {
    float x = starting_position.x;
    float y = starting_position.y;
    blocks_.reserve(blocks_design_.size() * blocks_design_[0].size());
    for (auto& blocks_line_ : blocks_design_) {
        x = starting_position.x;
        for (bool should_insert_block : blocks_line_) {
            if (should_insert_block) {
                blocks_.emplace_back(std::make_unique<DefenseBlock::Block>(
                    engine_, Rectangle{x, y, kDefenseBlockWidth, kDefenseBlockHeight}));
            }
            x += kDefenseBlockWidth;
        }
        y += kDefenseBlockHeight;
    }
}

void DefenseBlock::CleanMarkedBlocks() {
    auto should_remove_block = [](const auto& block) { return block->IsMarkedForDestroy(); };
    blocks_.erase(
        std::remove_if(blocks_.begin(), blocks_.end(), should_remove_block),
        blocks_.end());
}

void DefenseBlock::Render() {
    for (auto& block : blocks_) {
        block->Render();
    }
}
