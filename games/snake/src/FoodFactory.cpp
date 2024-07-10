#include "snake/include/FoodFactory.h"

#include <iostream>

namespace {
    static const float kFoodWidth = 20.f;
    static const float kFoodHeight = 20.f;
}

FoodFactory::FoodFactory(Engine& engine, const Snake& snake) 
    : engine_(engine)
    , snake_(snake) {
    InitSpawnPositions();
}

void FoodFactory::InitSpawnPositions() {
    const float every_x = 25.f;
    const float every_y = 25.f;
    for (float x = every_x; x < 800.f; x += every_x) {
        for (float y = every_y; y < 600.f; y += every_y) {
            spawn_positions_.emplace_back(x, y, kFoodWidth, kFoodHeight);
        }
    }
}

std::unique_ptr<Food> FoodFactory::CreateFood() {
    auto& random_generator = engine_.GetRandomGenerator();
    Rectangle random_rect;
    std::cout << "----- Spawn Food -------\n";
    do {
        auto random_index = static_cast<std::size_t>(
            random_generator.Generate(0, static_cast<int>(spawn_positions_.size() - 1)));
        random_rect = spawn_positions_[random_index];
        std::cout << "rnd idx: " << random_index << "\n";
    } while(snake_.IsRectangleCollidingWithNode(random_rect));
    std::cout << "------------------------\n";

    return std::make_unique<Food>(engine_, random_rect);
}