#pragma once

#include "engine/Engine.h"

#include "Snake.h"
#include "Food.h"

#include <memory>

class FoodFactory {
public:
    FoodFactory(Engine& engine, const Snake& snake);

    std::unique_ptr<Food> CreateFood();

private:
    Engine& engine_;
    const Snake& snake_;

    std::vector<Rectangle> spawn_positions_;
    void InitSpawnPositions();
};
