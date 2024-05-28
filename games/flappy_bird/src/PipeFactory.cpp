#pragma once

#include "flappy_bird/include/PipeFactory.h"

#include "engine/utils/Vec2.h"

namespace {
    static const int kPipeMinimumHeight = 200;
    static const int kSpaceBetweenPipePair = 150;
}

PipeFactory::PipeFactory(Engine& engine) 
    : engine_(engine) {}

std::unique_ptr<Pipe> PipeFactory::CreatePipe(float x, float y, float height) {
    return std::make_unique<Pipe>(engine_, Vec2{x, y}, height);
}

std::pair<std::unique_ptr<Pipe>, std::unique_ptr<Pipe>> PipeFactory::CreatePipePair() {
    auto& random_generator = engine_.GetRandomGenerator();
    const int pipe1_height = random_generator.Generate(
        kPipeMinimumHeight,
        engine_.GetWindowHeight() - kPipeMinimumHeight);
    
    const float x1 = static_cast<float>(engine_.GetWindowWidth());
    const float y1 = 0.f;

    float x2 = x1;
    float y2 = static_cast<float>(pipe1_height + kSpaceBetweenPipePair);
    const float pipe2_height = static_cast<float>(engine_.GetWindowHeight()) - y2;
    return {CreatePipe(x1, y1, static_cast<float>(pipe1_height)),
            CreatePipe(x2, y2, pipe2_height)};
}
