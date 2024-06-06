#include "flappy_bird/include/PipesPairFactory.h"

#include "engine/utils/Vec2.h"

PipesPairFactory::PipesPairFactory(Engine& engine, const Rectangle& floor) 
    : engine_(engine)
    , floor_(floor) {}

std::unique_ptr<PipesPair> PipesPairFactory::CreatePipesPair() {
    const float x = static_cast<float>(engine_.GetWindowWidth());
    
    auto& random_generator = engine_.GetRandomGenerator();
    const int height_without_floor = engine_.GetWindowHeight() - static_cast<int>(floor_.h);
    const int pipe_top_max_height = height_without_floor - static_cast<int>(PipesPair::kPipesGap) - static_cast<int>(Pipe::kMinimumHeight);
    const float pipe_height_top = static_cast<float>(random_generator.Generate(
        static_cast<int>(Pipe::kMinimumHeight), pipe_top_max_height));
    
    const float pipe_height_bottom = static_cast<float>(height_without_floor) - pipe_height_top - PipesPair::kPipesGap;
    return std::make_unique<PipesPair>(engine_, x, pipe_height_top, pipe_height_bottom);
}

