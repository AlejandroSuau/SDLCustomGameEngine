#include "flappy_bird/include/PipesPairFactory.h"

#include "flappy_bird/include/Constants.h"

PipesPairFactory::PipesPairFactory(Engine& engine, float floor_height) 
    : engine_(engine)
    , floor_height_(floor_height) {}

std::unique_ptr<PipesPair> PipesPairFactory::CreatePipesPair() {
    const float x = static_cast<float>(engine_.GetWindowWidth());
    
    auto& random_generator = engine_.GetRandomGenerator();
    const int height_without_floor = engine_.GetWindowHeight() - static_cast<int>(floor_height_);
    const int pipe_top_max_height = height_without_floor - 
                                    static_cast<int>(kPipesPairGap) -
                                    static_cast<int>(kPipeMinimumHeight);
    const float pipe_height_top = static_cast<float>(random_generator.Generate(
        static_cast<int>(kPipeMinimumHeight), pipe_top_max_height));
    
    const float pipe_height_bottom = static_cast<float>(height_without_floor) - pipe_height_top - kPipesPairGap;
    
    return std::make_unique<PipesPair>(engine_, x, pipe_height_top, pipe_height_bottom);
}

