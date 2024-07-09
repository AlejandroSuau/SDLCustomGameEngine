#pragma once

#include "engine/utils/Vec2.h"
#include "engine/Rectangle.h"
#include "engine/Engine.h"
#include "engine/collision/ICollidable.h"

#include <array>
#include <vector>
#include <memory>

class DefenseBlock {
public:
    DefenseBlock(Engine& engine, Vec2 position);

    void Render();
    void CleanMarkedBlocks();

private:
    class Block : public ICollidable {
    public:
        Block(Engine& engine, Rectangle rect);
        ~Block();
        
        void Render();
        bool IsMarkedForDestroy() const;
        
        // ICollidable
        const Rectangle& GetBoundingBox() const override;
        void OnCollision(ICollidable& other) override;
        unsigned int GetLayer() const override;
        unsigned int GetMask() const override;

    private:
        Engine& engine_;
        Rectangle rect_;
        bool is_marked_for_destroy_;
    };

    Engine& engine_;
    int lifes_;
    std::vector<std::unique_ptr<Block>> blocks_;

    std::array<std::array<bool, 7>, 7> blocks_design_ {{
        {0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1}
    }};

    void InitBlocks(Vec2 starting_position);
};
